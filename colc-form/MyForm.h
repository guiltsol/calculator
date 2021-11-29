#pragma once
#include "..\mp2-lab3-stack\TCalculator.h"
#include <msclr\marshal_cppstd.h>
namespace colcform {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:


	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;






	protected:






	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(301, 55);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(253, 42);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Калькулятор";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(424, 169);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(90, 46);
			this->button1->TabIndex = 3;
			this->button1->Text = L"=";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(166, 179);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(252, 31);
			this->textBox1->TabIndex = 4;
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::textBox1_KeyPress);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(520, 179);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(282, 31);
			this->textBox2->TabIndex = 5;
			this->textBox2->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox2_KeyDown);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(864, 454);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	



private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	std::string infix = msclr::interop::marshal_as<std::string>(textBox1->Text);

	if (String::IsNullOrEmpty((textBox1->Text)->Trim()))
	{
		textBox2->Text = "";
		return;
	}

	TCalculator calc;
	calc.SetExpr(infix);

	if (!calc.CheckExpr())
	{
		textBox2->Text = "Incorrect expression";
		return;
	}

	try
	{
		double result = calc.Calc();
		textBox2->Text = Convert::ToString(result);
	}
	catch (...)
	{
		textBox2->Text = "Incorrect expression";
	}
}

	   

private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar)
		&& e->KeyChar != '.' && e->KeyChar != '(' && e->KeyChar != ')'
		&& e->KeyChar != '+' && e->KeyChar != '-' && e->KeyChar != '*' && e->KeyChar != '/'
		&& e->KeyChar != '^' && e->KeyChar != 'e' && e->KeyChar != ' ')
	{
		e->Handled = true;
	}
	if (e->KeyChar == 127) e->Handled = true;
}
private: System::Void textBox2_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	if (e->KeyCode == Keys::Enter)
	{
		button1_Click(sender, e);
	}
}
};
}
