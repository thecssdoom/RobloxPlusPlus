#pragma once
#include <G3DAll.h>
#include "PropertyWindow.h"
#include "DataModelV2/TextButtonInstance.h"
#include "DataModelV2/ImageButtonInstance.h"
#include "CameraController.h"
#include "IEBrowser.h"
#include "Mouse.h"
#include "Tool/Tool.h"
#include "XplicitNgine/XplicitNgine.h"
//#include "GuiRoot.h"

class TextButtonInstance;
class ImageButtonInstance;
class PartInstance;
class CameraController;

class Application { // : public GApp {
	public:
		Application(HWND parentWindow);
		void Boop();
		virtual			~Application() {}
		virtual void	exitApplication();
		virtual void	onInit();
		virtual void	onLogic();
		virtual void	onNetwork();
		virtual void	onSimulation(RealTime rdt, SimTime sdt, SimTime idt);
		virtual void	onGraphics(RenderDevice* rd);
		virtual void	onUserInput(UserInput* ui);
		virtual void	onCleanup();
		void			clearInstances();
		void			navigateToolbox(std::string);
		PartInstance*	makePart();
		void			drawButtons(RenderDevice* rd);
		void			drawOutline(Vector3 from, Vector3 to, RenderDevice* rd, LightingParameters lighting, Vector3 size, Vector3 pos, CoordinateFrame c);
		void		deleteInstance();
		void		run();
		void		QuitApp();
		void		resizeWithParent(HWND parentWindow);
		void		onCreate(HWND parentWindow);
		void		onKeyPressed(int key);
		void		onKeyUp(int key);
		void		onMouseLeftPressed(HWND hwnd,int x, int y);
		void		onMouseLeftUp(RenderDevice* renderDevice, int x, int y);
		void		onMouseRightPressed(int x, int y);
		void		onMouseRightUp(int x, int y);
		void		onMouseMoved(int x, int y);
		void		onMouseWheel(int x, int y, short delta);
		void		setFocus(bool isFocused);
		int			getMode();
		void		unSetMode();
		CameraController	cameraController;
		UserInput*			userInput;
		PropertyWindow*		_propWindow;

		void				generateShadowMap(const CoordinateFrame& lightViewMatrix) const;

		RenderDevice*		getRenderDevice();
		void				selectInstance(Instance* selectedInstance,PropertyWindow* propWindow);
		void				setMode(int mode);

		void				resize3DView(int w, int h);
		
		ShaderRef			shader_part;
		ShaderRef			shader_none;

		bool		viewportHasFocus();

#ifdef _DEBUG
		bool debug_isRotatingSky;

		int kp_dbg_sky;
		float debug_rotatingsky;
#endif

		Tool * tool;
		void changeTool(Tool *);
		Mouse mouse;
	private:
		bool				mouseMoveState;
		RenderDevice*		renderDevice;
		//void				initGUI();
		HWND				_hWndMain;
		SkyRef				sky;
		bool				quit;
		bool				mouseOnScreen;
		bool				rightButtonHolding;
		void				main();
		GWindow*			_window;
		HWND				_hwndToolbox;
		HWND				_buttonTest;
		HWND				_hwndRenderer;

		DataModelInstance*	_dataModel;
		XplicitNgine*		_xplicitNgine;
		G3D::TextureRef		shadowMap;
		std::string			_title;
		bool				_dragging;
		int					_mode;
		GAppSettings		_settings;
		double lightProjX, lightProjY, lightProjNear, lightProjFar;
		IEBrowser*		webBrowser;

	protected:
		Stopwatch           m_graphicsWatch;
		Stopwatch           m_logicWatch;
		Stopwatch           m_networkWatch;
		Stopwatch           m_userInputWatch;
		Stopwatch           m_simulationWatch;
		Stopwatch           m_waitWatch;
};
