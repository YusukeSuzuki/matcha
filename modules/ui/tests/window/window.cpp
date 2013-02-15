#include <matcha/ui/window.hpp>
#include <matcha/ui/application.hpp>

#include <iostream>

int
main(int argc, char* argv[])
{
	using namespace std;
	using namespace matcha;

	ui::application app;

	auto window = ui::window("test");

	window.resize(640,480).on_delete(
		[&app](ui::window&) -> void { cout << "quit" << endl; app.quit(); }).show();

	app.run();
	
	return 0;
}

