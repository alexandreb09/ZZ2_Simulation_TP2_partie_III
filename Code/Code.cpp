#include "form_main.h"

[System::STAThread]

int main(array<System::String ^> ^args) {
	System::Windows::Forms::Application::EnableVisualStyles();
	System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false);
	Code::form_main code;
	System::Windows::Forms::Application::Run(%code);

	return 0;
}