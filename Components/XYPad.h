#pragma once

#include <JuceHeader.h>

//class XYPadWithLabels : public Component
//{
//	XYPad& xyPad;
//
//	XYPadWithLabels(XYPad& pad) :
//		xyPad(pad)
//	{
//
//	};
//
//	void paint(Graphics& g) {
//
//	}
//
//	void resized() {
//
//	}
//};

class XYPad : public Component, Slider::Listener
{
public:
	const double pi = 2 * acos(0.0);

	enum class Axis {X, Y};

	class Thumb : public Component
	{
	public:
		Thumb()
		{
			constrainer.setMinimumOnscreenAmounts(thumbSize, thumbSize, thumbSize, thumbSize);
		};

		void paint(Graphics& g) override
		{
			g.setColour(Colours::white);
			g.fillEllipse(getLocalBounds().toFloat());
		};

		void mouseDown(const MouseEvent& event) override
		{
			dragger.startDraggingComponent(this, event);
		};

		void mouseDrag(const MouseEvent& event) override
		{
			dragger.dragComponent(this, event, &constrainer);
			if (moveCallback)
				moveCallback(getPosition().toDouble());
		};

		std::function<void(Point<double>)> moveCallback;

	private:
		ComponentDragger dragger;
		ComponentBoundsConstrainer constrainer;

		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Thumb)
	};

	ZxLookAndFeel& lnf;

	XYPad(ZxLookAndFeel& l) : 
		lnf(l)
	{
		addAndMakeVisible(thumb);
		thumb.moveCallback = [&](Point<double> position)
		{
			const std::lock_guard<std::mutex> lock(vectorMutex);
			const auto bounds = getLocalBounds().toDouble();

			const auto w = static_cast<double>(thumbSize);
			for (auto* slider : xSliders)
			{
				slider->setValue(jmap(position.getX(), 0.0, bounds.getWidth() - w, slider->getMinimum(), slider->getMaximum()));
			}
			for (auto* slider : ySliders)
			{
				slider->setValue(jmap(position.getY(), bounds.getHeight() - w, 0.0, slider->getMinimum(), slider->getMaximum()));
			}

			repaint();
		};
	};

	void resized() override
	{
		thumb.setBounds(getLocalBounds().withSizeKeepingCentre(thumbSize, thumbSize));
		if (!xSliders.empty())
			sliderValueChanged(xSliders[0]);
		if (!ySliders.empty())
			sliderValueChanged(ySliders[0]);
	};

	void paint(Graphics& g)
	{
		auto theme = lnf.themeManager->getCurrentTheme();

		g.setColour(theme.xyPadBackground);
		g.fillRoundedRectangle(getLocalBounds().toFloat(), 10.f);

		g.setColour(theme.xyPadBackground.brighter());

		auto halfX = getWidth() / 2;
		auto halfY = getHeight() / 2;

		const float xDashLength[] = { 3,3 };
		const float yDashLength[] = { 3,3 };

		auto line = Line<float>(0, halfY, getWidth()/2, halfY);
		g.drawDashedLine(line,&xDashLength[0], 2, 1.f, 0);

		line = Line<float>(getWidth(), halfY, getWidth() / 2, halfY);
		g.drawDashedLine(line, &xDashLength[0], 2, 1.f, 0);

		line = Line<float>(halfX, 0, halfX, getHeight()/2);
		g.drawDashedLine(line, &yDashLength[0], 2, 1.f, 0);

		line = Line<float>(halfX, getHeight(), halfX, getHeight() / 2);
		g.drawDashedLine(line, &yDashLength[0], 2, 1.f, 0);

		int thumbX = thumb.getX() + thumbSize/2;
		int thumbY = thumb.getY() + thumbSize/2;

		g.setColour(theme.xyPadBackground.brighter().brighter());
		g.drawLine(thumbX, 0, thumbX, getHeight());
		g.drawLine(0, thumbY, getWidth(), thumbY);

		auto bounds = getLocalBounds();
		bounds.removeFromLeft(5);
		bounds.removeFromRight(5);

		g.setColour(theme.textMain);
		g.setFont(lnf.fontRegular);

		auto bottomBounds = bounds.removeFromBottom(30);
		g.drawFittedText("0%", bottomBounds.removeFromLeft(30), Justification::centredLeft, 1);
		bottomBounds.removeFromRight(30);
		g.setFont(lnf.fontBold);
		g.drawFittedText(xSliders[0]->getName(), bottomBounds, Justification::centred, 1);

		auto topBounds = bounds.removeFromTop(30);
		g.drawFittedText("100%", topBounds.removeFromRight(30), Justification::centredRight, 1);
		
		g.setFont(lnf.fontBold);
		///g.drawMultiLineText("Vertical", bounds.getX(), lnf.fontSize, lnf.fontSize / 2, Justification::centred);

		float rotationInDegrees = -90;
		float rotationInRadians = pi * 2 * (rotationInDegrees / 360.f);

		GlyphArrangement ga;
		ga.addLineOfText(lnf.fontBold, ySliders[0]->getName(), 0, 0);
		Path p;
		ga.createPath(p);
		auto pathBounds = p.getBounds();//Rectangle<int>(0,0,getHeight(),lnf.fontSize * 2);//getLocalBounds().removeFromLeft(100);

		//DBG("In Radians: " << rotationInRadians);
		g.addTransform(AffineTransform()
			.rotated(rotationInRadians, pathBounds.getCentreX(), pathBounds.getCentreY())
			.translated(-lnf.fontSize/2, getHeight() / 2)
		);
		//g.drawFittedText("NAME", getLocalBounds(), Justification::centred, 1);

		g.fillPath(p);

	};

	void registerSlider(Slider* slider, Axis axis)
	{
		slider->addListener(this);
		const std::lock_guard<std::mutex> lock(vectorMutex);
		if (axis == Axis::X)
			xSliders.push_back(slider);
		if (axis == Axis::Y)
			ySliders.push_back(slider);
	};

	void deregisterSlider(Slider* slider)
	{
		slider->removeListener(this);
		const std::lock_guard<std::mutex> lock(vectorMutex);
		xSliders.erase(std::remove(xSliders.begin(), xSliders.end(), slider), xSliders.end());
		ySliders.erase(std::remove(ySliders.begin(), ySliders.end(), slider), ySliders.end());
	};

private:
	void sliderValueChanged(Slider* slider) override
	{
		if (thumb.isMouseOverOrDragging(false))
			return;

		const auto isXAxisSlider = std::find(xSliders.begin(), xSliders.end(), slider) != xSliders.end();
		const auto bounds = getLocalBounds().toDouble();
		const auto w = static_cast<double>(thumbSize);
		if (isXAxisSlider)
		{
			thumb.setTopLeftPosition(
				jmap(slider->getValue(), slider->getMinimum(), slider->getMaximum(), 0.0, bounds.getWidth() - w), thumb.getY()
			);
		}
		else {
			thumb.setTopLeftPosition(
				thumb.getX(), jmap(slider->getValue(), slider->getMinimum(), slider->getMaximum(), bounds.getHeight() - w, 0.0)
			);
		}
		repaint();
	};

	std::vector<Slider*> xSliders, ySliders;
	Thumb thumb;
	std::mutex vectorMutex;

	static constexpr int thumbSize = 20;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(XYPad);
};