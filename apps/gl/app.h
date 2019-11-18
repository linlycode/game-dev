#ifndef APP_H
#define APP_H

class Window;

class App {
public:
	App();
	App(const App &) = delete;
	~App();

	void pollEvents();

	bool shouldExit();

private:
	bool m_initialized;
	bool m_shouldExit;
};

#endif
