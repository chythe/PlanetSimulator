#pragma once

#include "CEGUI\CEGUI.h"
#include "CEGUI\RendererModules\OpenGL\GL3Renderer.h"
#include "Dependencies\glm\glm.hpp"


class GUI
{
private:
	static CEGUI::OpenGL3Renderer * m_renderer;
	CEGUI::GUIContext * m_context = nullptr;
	CEGUI::Window* m_root = nullptr;

public:
	void init(std::string resourceDirectory);
	void destroy();

	void draw();

	void loadScheme(const std::string schemeFile);
	void setFont(const std::string fontFile);
	CEGUI::Window* createWidget(const std::string type, const glm::vec4& destRectPerc, const glm::vec4& destRectPix, const std::string name = "");
	static void setWidgetDestRect(CEGUI::Window* widget, const glm::vec4& destRectPerc, const glm::vec4& destRectPix);


	static CEGUI::OpenGL3Renderer * getRenderer() { return m_renderer; }
	const CEGUI::GUIContext * getContext() { return m_context;  }
};

