#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include "jackylib.h"
#include <stdio.h>
#include <iostream>
#include <conio.h> 
namespace OpenCV_DiffObjRec {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace cv;
	using namespace jacky_lib;

	bool calibrationMode;// Cek Kalibrasi
	bool mouseIsDragging;// Cek nge drag ga?
	bool mouseMove;
	bool rectangleSelected;
	cv::Point initialClickPoint, currentMousePoint;// posisi titik awal dan mouse
	cv::Rect rectangleROI;// Range terpilih
	vector<int> H_ROI, S_ROI, V_ROI;// buat nyimpen HSV max (soalnya ga make RGB)

	const int FRAME_WIDTH = 640;// Video frame lebar size nya
	const int FRAME_HEIGHT = 480;// Video frame tinggi size nya
	int MIN_OBJECT_AREA;// Min objek area yang di tracking
	const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH / 1.5;// Max obj area yang di tracking
	Mat cameraframe;
	mat2picture mat2bmp;
	Mat inrImg;
	Mat hvsImg;
	Mat srcImg;// semua variabel mat yg bakal dipake buat imgpros di main
	int mHmax, mHmin, mVmax, mVmin, mSmax, mSmin;// HVS max,min value
	int HmaxObj1, HminObj1, VmaxObj1, VminObj1, SmaxObj1, SminObj1;
	int HmaxObj2, HminObj2, VmaxObj2, VminObj2, SmaxObj2, SminObj2;
	int HmaxObj3, HminObj3, VmaxObj3, VminObj3, SmaxObj3, SminObj3;
	int Max_obj = 50;// Max jumlah objek setelah di kontur
	int xm, ym;// x,y ROI
	num2str n2str;// konversi string ke char
	str2char string2char;
	/// <summary>
	/// Summary for MainForm
	/// </summary>
	void clickAndDrag_Rectangle(int event, int x, int y, int flags, void* param) {

			// klo di kalibrasi, pake mouse aja
		if (calibrationMode == true) 
		{
				// bakal parameter buat videonya trus dijadiin mat pointer
			Mat* videoFeed = (Mat*)param;

			if (event == CV_EVENT_LBUTTONDOWN && mouseIsDragging == false)
			{
					// ngetrack titik awal
				initialClickPoint = cv::Point(x, y);
					// ngedrag mouse nya
				mouseIsDragging = true;
			}
				// kondisi ngedrag mouse
			if (event == CV_EVENT_MOUSEMOVE && mouseIsDragging == true)
			{
				currentMousePoint = cv::Point(x, y);
				mouseMove = true;
			}
				// dapet rangenya
			if (event == CV_EVENT_LBUTTONUP && mouseIsDragging == true)
			{
					//nge set ROI nya
				rectangleROI = Rect(initialClickPoint, currentMousePoint);

					//ngereset boolean (biar bisa milih objek lagi klo yg tadi salah pilih)
				mouseIsDragging = false;
				mouseMove = false;
				rectangleSelected = true;
			}

			if (event == CV_EVENT_RBUTTONDOWN) 
			{
					//klik kanan mouse = reset HSV
				mHmin = 0;
				mSmin = 0;
				mVmin = 0;
				mHmax = 255;
				mSmax = 255;
				mVmax = 255;

			}
			
			if (event == CV_EVENT_MBUTTONDOWN) 
			{
				//tambahan aja, klo pengen
			}

		}

	}
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// </summary>

			//ini bakal bikin form nya biar ga pusing
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  txbSmin;
	private: System::Windows::Forms::TextBox^  txbSmax;
	private: System::Windows::Forms::TextBox^  txbVmin;
	private: System::Windows::Forms::TextBox^  txbVmax;
	private: System::Windows::Forms::TextBox^  txbHmin;
	private: System::Windows::Forms::TextBox^  txbHmax;
	private: System::Windows::Forms::TrackBar^  trbSmax;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TrackBar^  trbSmin;
	private: System::Windows::Forms::TrackBar^  trbVmax;
	private: System::Windows::Forms::TrackBar^  trbVmin;
	private: System::Windows::Forms::TrackBar^  trbHmax;
	private: System::Windows::Forms::TrackBar^  trbHmin;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  txtObject3;
	private: System::Windows::Forms::TextBox^  txtObject2;
	private: System::Windows::Forms::TextBox^  txtObject1;
	private: System::Windows::Forms::RadioButton^  rbtObject3;
	private: System::Windows::Forms::RadioButton^  rbtObject2;
	private: System::Windows::Forms::RadioButton^  rbtObject1;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::CheckBox^  cbxRegion;

	protected:

	private:
		/// <summary>
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// </summary>
			//desain form nya
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txbSmin = (gcnew System::Windows::Forms::TextBox());
			this->txbSmax = (gcnew System::Windows::Forms::TextBox());
			this->txbVmin = (gcnew System::Windows::Forms::TextBox());
			this->txbVmax = (gcnew System::Windows::Forms::TextBox());
			this->txbHmin = (gcnew System::Windows::Forms::TextBox());
			this->txbHmax = (gcnew System::Windows::Forms::TextBox());
			this->trbSmax = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->trbSmin = (gcnew System::Windows::Forms::TrackBar());
			this->trbVmax = (gcnew System::Windows::Forms::TrackBar());
			this->trbVmin = (gcnew System::Windows::Forms::TrackBar());
			this->trbHmax = (gcnew System::Windows::Forms::TrackBar());
			this->trbHmin = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->cbxRegion = (gcnew System::Windows::Forms::CheckBox());
			this->txtObject3 = (gcnew System::Windows::Forms::TextBox());
			this->txtObject2 = (gcnew System::Windows::Forms::TextBox());
			this->txtObject1 = (gcnew System::Windows::Forms::TextBox());
			this->rbtObject3 = (gcnew System::Windows::Forms::RadioButton());
			this->rbtObject2 = (gcnew System::Windows::Forms::RadioButton());
			this->rbtObject1 = (gcnew System::Windows::Forms::RadioButton());
			this->label10 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmax))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmin))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Mulai";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(93, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(62, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L" "; //Tree Status
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(161, 17);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(20, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L" "; //sts
			// 
			// txbSmin
			// 
			this->txbSmin->Location = System::Drawing::Point(244, 308);
			this->txbSmin->Name = L"txbSmin";
			this->txbSmin->Size = System::Drawing::Size(42, 20);
			this->txbSmin->TabIndex = 23;
			// 
			// txbSmax
			// 
			this->txbSmax->Location = System::Drawing::Point(244, 257);
			this->txbSmax->Name = L"txbSmax";
			this->txbSmax->Size = System::Drawing::Size(42, 20);
			this->txbSmax->TabIndex = 22;
			// 
			// txbVmin
			// 
			this->txbVmin->Location = System::Drawing::Point(244, 206);
			this->txbVmin->Name = L"txbVmin";
			this->txbVmin->Size = System::Drawing::Size(42, 20);
			this->txbVmin->TabIndex = 21;
			// 
			// txbVmax
			// 
			this->txbVmax->Location = System::Drawing::Point(244, 155);
			this->txbVmax->Name = L"txbVmax";
			this->txbVmax->Size = System::Drawing::Size(42, 20);
			this->txbVmax->TabIndex = 20;
			// 
			// txbHmin
			// 
			this->txbHmin->Location = System::Drawing::Point(244, 104);
			this->txbHmin->Name = L"txbHmin";
			this->txbHmin->Size = System::Drawing::Size(42, 20);
			this->txbHmin->TabIndex = 19;
			// 
			// txbHmax
			// 
			this->txbHmax->Location = System::Drawing::Point(244, 53);
			this->txbHmax->Name = L"txbHmax";
			this->txbHmax->Size = System::Drawing::Size(42, 20);
			this->txbHmax->TabIndex = 18;
			// 
			// trbSmax
			// 
			this->trbSmax->Location = System::Drawing::Point(52, 308);
			this->trbSmax->Maximum = 500;
			this->trbSmax->Name = L"trbSmax";
			this->trbSmax->Size = System::Drawing::Size(186, 45);
			this->trbSmax->TabIndex = 10;
			this->trbSmax->Value = 97;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(11, 257);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(33, 13);
			this->label3->TabIndex = 16;
			this->label3->Text = L"Smax";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(11, 155);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(33, 13);
			this->label4->TabIndex = 17;
			this->label4->Text = L"Vmax";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 308);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(30, 13);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Smin";
			this->label6->Click += gcnew System::EventHandler(this, &MainForm::label6_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(11, 206);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(30, 13);
			this->label5->TabIndex = 14;
			this->label5->Text = L"Vmin";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(10, 104);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(31, 13);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Hmin";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(11, 53);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(34, 13);
			this->label8->TabIndex = 12;
			this->label8->Text = L"Hmax";
			// 
			// trbSmin
			// 
			this->trbSmin->Location = System::Drawing::Point(52, 257);
			this->trbSmin->Maximum = 500;
			this->trbSmin->Name = L"trbSmin";
			this->trbSmin->Size = System::Drawing::Size(186, 45);
			this->trbSmin->TabIndex = 9;
			this->trbSmin->Value = 500;
			// 
			// trbVmax
			// 
			this->trbVmax->Location = System::Drawing::Point(52, 206);
			this->trbVmax->Maximum = 500;
			this->trbVmax->Name = L"trbVmax";
			this->trbVmax->Size = System::Drawing::Size(186, 45);
			this->trbVmax->TabIndex = 8;
			this->trbVmax->Value = 85;
			// 
			// trbVmin
			// 
			this->trbVmin->Location = System::Drawing::Point(52, 155);
			this->trbVmin->Maximum = 500;
			this->trbVmin->Name = L"trbVmin";
			this->trbVmin->Size = System::Drawing::Size(186, 45);
			this->trbVmin->TabIndex = 7;
			this->trbVmin->Value = 160;
			// 
			// trbHmax
			// 
			this->trbHmax->Location = System::Drawing::Point(52, 104);
			this->trbHmax->Maximum = 500;
			this->trbHmax->Name = L"trbHmax";
			this->trbHmax->Size = System::Drawing::Size(186, 45);
			this->trbHmax->TabIndex = 6;
			this->trbHmax->Value = 9;
			// 
			// trbHmin
			// 
			this->trbHmin->Location = System::Drawing::Point(52, 53);
			this->trbHmin->Maximum = 500;
			this->trbHmin->Name = L"trbHmin";
			this->trbHmin->Size = System::Drawing::Size(186, 45);
			this->trbHmin->TabIndex = 11;
			this->trbHmin->Value = 69;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(77, 359);
			this->trackBar1->Maximum = 100;
			this->trackBar1->Minimum = 5;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(209, 45);
			this->trackBar1->TabIndex = 24;
			this->trackBar1->Value = 10;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(9, 368);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(62, 13);
			this->label9->TabIndex = 15;
			this->label9->Text = L"Defect Size";
			this->label9->Click += gcnew System::EventHandler(this, &MainForm::label6_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->cbxRegion);
			this->groupBox1->Controls->Add(this->txtObject3);
			this->groupBox1->Controls->Add(this->txtObject2);
			this->groupBox1->Controls->Add(this->txtObject1);
			this->groupBox1->Controls->Add(this->rbtObject3);
			this->groupBox1->Controls->Add(this->rbtObject2);
			this->groupBox1->Controls->Add(this->rbtObject1);
			this->groupBox1->Controls->Add(this->label10);
			this->groupBox1->Location = System::Drawing::Point(303, 17);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 377);
			this->groupBox1->TabIndex = 25;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Kalibrasi";
			// 
			// cbxRegion
			// 
			this->cbxRegion->AutoSize = true;
			this->cbxRegion->Location = System::Drawing::Point(13, 151);
			this->cbxRegion->Name = L"cbxRegion";
			this->cbxRegion->Size = System::Drawing::Size(148, 17);
			this->cbxRegion->TabIndex = 3;
			this->cbxRegion->Text = L"Aktifkan Region Kalibrasi";
			this->cbxRegion->UseVisualStyleBackColor = true;
			// 
			// txtObject3
			// 
			this->txtObject3->Location = System::Drawing::Point(94, 98);
			this->txtObject3->Name = L"txtObject3";
			this->txtObject3->Size = System::Drawing::Size(100, 20);
			this->txtObject3->TabIndex = 2;
			// 
			// txtObject2
			// 
			this->txtObject2->Location = System::Drawing::Point(94, 64);
			this->txtObject2->Name = L"txtObject2";
			this->txtObject2->Size = System::Drawing::Size(100, 20);
			this->txtObject2->TabIndex = 2;
			// 
			// txtObject1
			// 
			this->txtObject1->Location = System::Drawing::Point(94, 29);
			this->txtObject1->Name = L"txtObject1";
			this->txtObject1->Size = System::Drawing::Size(100, 20);
			this->txtObject1->TabIndex = 2;
			// 
			// rbtObject3
			// 
			this->rbtObject3->AutoSize = true;
			this->rbtObject3->Location = System::Drawing::Point(13, 101);
			this->rbtObject3->Name = L"rbtObject3";
			this->rbtObject3->Size = System::Drawing::Size(65, 17);
			this->rbtObject3->TabIndex = 1;
			this->rbtObject3->Text = L"Objek 3";
			this->rbtObject3->UseVisualStyleBackColor = true;
			// 
			// rbtObject2
			// 
			this->rbtObject2->AutoSize = true;
			this->rbtObject2->Location = System::Drawing::Point(13, 65);
			this->rbtObject2->Name = L"rbtObject2";
			this->rbtObject2->Size = System::Drawing::Size(65, 17);
			this->rbtObject2->TabIndex = 1;
			this->rbtObject2->Text = L"Objek 2";
			this->rbtObject2->UseVisualStyleBackColor = true;
			// 
			// rbtObject1
			// 
			this->rbtObject1->AutoSize = true;
			this->rbtObject1->Checked = true;
			this->rbtObject1->Location = System::Drawing::Point(13, 31);
			this->rbtObject1->Name = L"rbtObject1";
			this->rbtObject1->Size = System::Drawing::Size(65, 17);
			this->rbtObject1->TabIndex = 1;
			this->rbtObject1->TabStop = true;
			this->rbtObject1->Text = L"Objek 1";
			this->rbtObject1->UseVisualStyleBackColor = true;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(6, 36);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(0, 13);
			this->label10->TabIndex = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(515, 406);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->txbSmin);
			this->Controls->Add(this->txbSmax);
			this->Controls->Add(this->txbVmin);
			this->Controls->Add(this->txbVmax);
			this->Controls->Add(this->txbHmin);
			this->Controls->Add(this->txbHmax);
			this->Controls->Add(this->trbSmax);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->trbSmin);
			this->Controls->Add(this->trbVmax);
			this->Controls->Add(this->trbVmin);
			this->Controls->Add(this->trbHmax);
			this->Controls->Add(this->trbHmin);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MainForm";
			this->Text = L"iyain";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbSmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbVmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmax))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHmin))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		calibrationMode = true;
		VideoCapture videocap;
		//videocap.open("namavideo.mp4");// klo videonya rekaman
		videocap.open(0);// klo realtime
		if (!videocap.isOpened()) {
			MessageBox::Show("Gagal buka video/webcam");
			_getch();
			return;
		}
		videocap.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);// ngeset ukuran frame (dari declare d atas)
		videocap.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);
		while (1)// looping trus sampe video kelar
		{
			setMouseCallback("video", clickAndDrag_Rectangle, &srcImg);
			
				// ngambil HSV dari trackbar
				// ini fungsi jadi klo mau ganti objek, radio button nya pilih dulu
			if (rbtObject1->Checked == true && cbxRegion->Checked == false)
			{
				updateHSV(HmaxObj1, HminObj1, VmaxObj1, VminObj1, SmaxObj1, SminObj1);
			}
			else if (rbtObject2->Checked == true && cbxRegion->Checked == false)
			{
				updateHSV(HmaxObj2, HminObj2, VmaxObj2, VminObj2, SmaxObj2, SminObj2);
			}
			else if (rbtObject3->Checked == true && cbxRegion->Checked == false)
			{
				updateHSV(HmaxObj3, HminObj3, VmaxObj3, VminObj3, SmaxObj3, SminObj3);
			}

			MIN_OBJECT_AREA = trackBar1->Value*trackBar1->Value;

			videocap.read(srcImg);// ngambil dari video
			resize(srcImg, srcImg, cv::Size(FRAME_WIDTH, FRAME_HEIGHT));
				// mulai imgpros
			cvtColor(srcImg, hvsImg, COLOR_BGR2HSV);// disini diubah colornya ke HSV
														//imshow("HVS", hvsImg);

			recordHSV_Values(srcImg, hvsImg);



			if (rbtObject1->Checked == true&&cbxRegion->Checked == true)
			{
				autoupdateHSV(HmaxObj1, HminObj1, VmaxObj1, VminObj1, SmaxObj1, SminObj1);
			}
			else if (rbtObject2->Checked == true && cbxRegion->Checked == true)
			{
				autoupdateHSV(HmaxObj2, HminObj2, VmaxObj2, VminObj2, SmaxObj2, SminObj2);
			}
			else if (rbtObject3->Checked == true && cbxRegion->Checked == true)
			{
				autoupdateHSV(HmaxObj3, HminObj3, VmaxObj3, VminObj3, SmaxObj3, SminObj3);
			}
			
			string obj1_name, obj2_name, obj3_name;
			if (txtObject1->Text == "")
			{
				obj1_name = "Objek 1";
			}
			else obj1_name =string2char.ConvertString2Char(txtObject1->Text);

			if (txtObject2->Text == "")
			{
				obj2_name = "Objek 2";
			}
			else obj2_name = string2char.ConvertString2Char(txtObject2->Text);

			if (txtObject3->Text == "")
			{
				obj3_name = "Objek 3";
			}
			else obj3_name = string2char.ConvertString2Char(txtObject3->Text);
			
			objFilter(HmaxObj1, HminObj1, VmaxObj1, VminObj1, SmaxObj1, SminObj1, hvsImg,obj1_name,"1haha" );
			objFilter(HmaxObj2, HminObj2, VmaxObj2, VminObj2, SmaxObj2, SminObj2, hvsImg,obj2_name, "2haha");
			objFilter(HmaxObj3, HminObj3, VmaxObj3, VminObj3, SmaxObj3, SminObj3, hvsImg, obj3_name, "3haha");
				// Abis itu ditampilin objek apa aja yg dilihat (objek 1-3)
				//resize(srcImg, srcImg, cv::Size(320, 240));
				//ptbVideo->Image = mat2bmp.Mat2Bimap(srcImg); // Mat convert to BMP we use from jackylib library
				//ptbVideo->Refresh();
			imshow("video", srcImg);
			if (waitKey(30) == 27)
				break;
		}

	}
	private: void objFilter(int& Hmax, int& Hmin, int& Vmax, int& Vmin, int& Smax, int& Smin,Mat inputImage, string objectName,string binwd)
	{
		vector <vector<int>> objs;// buat objek vektornya
		inRange(inputImage, Scalar(Hmin, Smin, Vmin), Scalar(Hmax, Smax, Vmax), inrImg);// filter obj warna
		Mat erode_element = getStructuringElement(MORPH_RECT, cv::Size(4, 4));
		Mat dilate_element = getStructuringElement(MORPH_RECT, cv::Size(8, 8));
		erode(inrImg, inrImg, erode_element);
		erode(inrImg, inrImg, erode_element);
		//imshow("Erode", inrImg);
		dilate(inrImg, inrImg, dilate_element);
		dilate(inrImg, inrImg, dilate_element);
		//dilate(inrImg, inrImg, dilate_element);
		Mat showbin;
		resize(inrImg, showbin, cv::Size(320, 240));
		imshow(binwd, showbin);

			//abis di filter, cari kontur nya
		Mat temps;// declare var nya mat buat imgpros
		inrImg.copyTo(temps);// kopi InrImg ke Temps

		vector<vector<cv::Point>> conts;
		vector<Vec4i> hier;
		findContours(temps, conts, hier, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);// nyari kontur & hier biar bisa nyari objek

		double arearef = 0;
		bool objFound = false;
		if (hier.size() > 0)// hier: jumlah objek setelah proses kontur
		{
			int obj_qty = hier.size();
			if (obj_qty < Max_obj)	
			{
				for (int idx = 0; idx >= 0; idx = hier[idx][0]) {
					Moments moms = moments((cv::Mat)conts[idx]);// libnya open cv ini
					double area = moms.m00;
					if (area > MIN_OBJECT_AREA)// jika area berada diarea yg udh di deff, objek ketemu
					{
						vector <int> object;
						object.push_back(moms.m10 / area);
						object.push_back(moms.m01 / area);
						objs.push_back(object);
						objFound = true;
					}
					else
					{
						objFound = false;
					}
				}
			}
			if (objFound == true)// klo ketemu, kasi buletan
			{
				putText(srcImg, "Objek ketemu!", cv::Point(0, 50), 2, 1, Scalar(0, 0, 255), 2);
				for (int i = 0; i < objs.size(); i++) {
					//cv::circle(srcImg, cv::Point(objs.at(i).at(0), objs.at(i).at(1)), 20, cv::Scalar(225, 0, 0), 2);
					cv::putText(srcImg, objectName, cv::Point(objs.at(i).at(0), objs.at(i).at(1) + 45), 1, 1, Scalar(255, 0, 0));
				}
			}

		}
	}
	private: void updateHSV(int& Hmax, int& Hmin, int& Vmax, int& Vmin, int& Smax, int& Smin)
	{
		Hmin = trbHmax->Value;
		Hmax = trbHmin->Value;
		Vmin = trbVmax->Value;
		Vmax = trbVmin->Value;
		Smin = trbSmax->Value;
		Smax = trbSmin->Value;
		txbHmax->Text = Hmax.ToString();
		txbHmin->Text = Hmin.ToString();
		txbVmin->Text = Vmin.ToString();
		txbVmax->Text = Vmax.ToString();
		txbSmin->Text = Smin.ToString();
		txbSmax->Text = Smax.ToString();
	}
	private: void autoupdateHSV(int& Hmax, int& Hmin, int& Vmax, int& Vmin, int& Smax, int& Smin)
	{
	
		Hmax = mHmax;
		Hmin = mHmin;
		Vmax = mVmax;
		Vmin = mVmin;
		Smax = mSmax;
		Smin = mSmin;
		trbHmax->Value = mHmin;
		trbHmin->Value = mHmax;
		trbVmax->Value = mVmin;
		trbVmin->Value = mVmax;
		trbSmax->Value = mSmin;
		trbSmin->Value = mSmax;
	}
	private: void recordHSV_Values(cv::Mat frame, cv::Mat hsv_frame) {

			//Nyimpen value HSV bakal ROI gapake mouse
		if (mouseMove == false && rectangleSelected == true) {

				//clear value sebelum dulu
			if (H_ROI.size() > 0) H_ROI.clear();
			if (S_ROI.size() > 0) S_ROI.clear();
			if (V_ROI.size() > 0)V_ROI.clear();

			if (rectangleROI.width < 1 || rectangleROI.height < 1) cout << "jangan garis doang !" << endl;
			else {
				for (int i = rectangleROI.x; i < rectangleROI.x + rectangleROI.width; i++) {
						//iterasi X dan Y, dan nyimpen HSV value
					for (int j = rectangleROI.y; j < rectangleROI.y + rectangleROI.height; j++) {
							//nyimpen HSV berdasar titik2 ini
						H_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[0]);
						S_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[1]);
						V_ROI.push_back((int)hsv_frame.at<cv::Vec3b>(j, i)[2]);
					}
				}
			}
				//reset biar klo salah bisa detek ulang warnanya
			rectangleSelected = false;
				//nge set min max trus simpen dalam bentuk array

			if (H_ROI.size() > 0) {
					//min_element&max nya harus dikasih bintang biar ga return itteration
				mHmin = *std::min_element(H_ROI.begin(), H_ROI.end());
				mHmax = *std::max_element(H_ROI.begin(), H_ROI.end());
				cout << "MIN 'H' VALUE: " << mHmin << endl;
				cout << "MAX 'H' VALUE: " << mHmax << endl;
			}
			if (S_ROI.size() > 0) {
				mSmin = *std::min_element(S_ROI.begin(), S_ROI.end());
				mSmax = *std::max_element(S_ROI.begin(), S_ROI.end());
				cout << "MIN 'S' VALUE: " << mSmin << endl;
				cout << "MAX 'S' VALUE: " << mSmax << endl;
			}
			if (V_ROI.size() > 0) {
				mVmin = *std::min_element(V_ROI.begin(), V_ROI.end());
				mVmax = *std::max_element(V_ROI.begin(), V_ROI.end());
				cout << "MIN 'V' VALUE: " << mSmin << endl;
				cout << "MAX 'V' VALUE: " << mSmax << endl;
			}

		}

		if (mouseMove == true) {
				//klo mouse gerak nentuin titik pake mouse
			rectangle(frame, initialClickPoint, cv::Point(currentMousePoint.x, currentMousePoint.y), cv::Scalar(0, 255, 0), 1, 8, 0);
		}


	}
	private: System::Void label6_Click(System::Object^  sender, System::EventArgs^  e) {
	}
};
}
