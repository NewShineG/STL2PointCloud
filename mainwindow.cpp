#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, settings(SETTINGSPATH, QSettings::IniFormat)
{


	ui->setupUi(this);

	if (settings.contains("filePath"))
	{
		filePath = settings.value("filePath").toString();
	}
	if (settings.contains("mPrecisionX"))
	{
		ui->stepXSpinBox->setValue(settings.value("mPrecisionX").toDouble());
		s2pd.mPrecisionX = settings.value("mPrecisionX").toDouble();
	}
	if (settings.contains("mPrecisionY"))
	{
		ui->stepYSpinBox->setValue(settings.value("mPrecisionY").toDouble());
		s2pd.mPrecisionY = settings.value("mPrecisionY").toDouble();
	}
	if (settings.contains("mPrecisionZ"))
	{
		ui->stepZSpinBox->setValue(settings.value("mPrecisionZ").toDouble());
		s2pd.mPrecisionZ = settings.value("mPrecisionZ").toDouble();
		s2pd.allowError = s2pd.mPrecisionZ / 100;
	}
	if (settings.contains("BMPpitchX"))
	{
		ui->pitchXSpinBox->setValue(settings.value("BMPpitchX").toDouble());
		BMPpitchX = settings.value("BMPpitchX").toDouble();
	}
	if (settings.contains("BMPpitchY"))
	{
		ui->pitchYSpinBox->setValue(settings.value("BMPpitchY").toDouble());
		BMPpitchY = settings.value("BMPpitchY").toDouble();
	}
	if (settings.contains("BMPwidth"))
	{
		BMPwidth = settings.value("BMPwidth").toDouble();
	}
	if (settings.contains("BMPlength"))
	{
		BMPlength = settings.value("BMPlength").toDouble();
	}


	connect(ui->stepXSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
		s2pd.mPrecisionX = ui->stepXSpinBox->value();
	});
	connect(ui->stepYSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
		s2pd.mPrecisionY = ui->stepYSpinBox->value();
	});
	connect(ui->stepZSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
		s2pd.mPrecisionZ = ui->stepZSpinBox->value();
		s2pd.allowError = s2pd.mPrecisionZ / 100;
	});
	connect(ui->pitchXSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
		BMPpitchX = ui->pitchXSpinBox->value();
	});
	connect(ui->pitchYSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this]() {
		BMPpitchY = ui->pitchYSpinBox->value();
	});

}

MainWindow::~MainWindow()
{
	settings.setValue("filePath", filePath);
	settings.setValue("mPrecisionX", s2pd.mPrecisionX);
	settings.setValue("mPrecisionY", s2pd.mPrecisionY);
	settings.setValue("mPrecisionZ", s2pd.mPrecisionZ);
	settings.setValue("BMPwidth", BMPwidth);
	settings.setValue("BMPlength", BMPlength);
	settings.setValue("BMPpitchX", BMPpitchX);
	settings.setValue("BMPpitchY", BMPpitchY);

	delete ui;
}


void MainWindow::on_readSTLButton_clicked()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Read file", filePath, "STL files (*.STL)");
	QFileInfo fileInfo(fileName);
	filePath = fileInfo.path();
	fileName.replace("/", "\\");
	s2pd.stlstrpath = fileName.toStdString();
	if (!s2pd.readStl())
	{
		QMessageBox::critical(this, tr("Error"), tr("readSTL Error"),
			 QMessageBox::Discard, QMessageBox::Discard);

	}
	return;
}

void MainWindow::on_toPointCloudButton_clicked()
{
	s2pd.Slice_STL();
	ui->layerNumLabel->setText(QString::number(s2pd.slicenumber_total));
	s2pd.find_closedContours();
	s2pd.to3DMatrix();
	return;
}

void MainWindow::on_toTXTButton_clicked()
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save file", filePath, "Text files (*.txt)");
	if (!fileName.isEmpty())
	{
		QFile file(fileName);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			// 创建进度提示框
			QProgressDialog progressDialog("toTXT", "取消", 0, s2pd.slicenumber_total);
			progressDialog.setWindowTitle(QString("toTXT"));
			progressDialog.setLabelText(QString("toTXT.."));
			progressDialog.setValue(0);
			progressDialog.setWindowModality(Qt::WindowModal);
			progressDialog.setAutoClose(false);
			progressDialog.setAutoReset(false);
			progressDialog.show();
			QApplication::processEvents();


			QTextStream stream(&file);
			for (int znum = 0; znum < s2pd.slicenumber_total; znum++)
			{
				for (int pnum = 0; pnum < s2pd.Solid[znum].pointCloud.size(); pnum++)
				{
					stream << QString::number(s2pd.Solid[znum].pointCloud[pnum].x * 1000) << ","
						<< QString::number(s2pd.Solid[znum].pointCloud[pnum].y * 1000) << ","
						<< QString::number(s2pd.Solid[znum].pointCloud[pnum].z * 1000) << endl;
				}

				if (ui->initStartCheckBox->isChecked() && s2pd.Solid[znum].pointCloud.size() > 0)
				{
					stream << "-999999,-999999," << QString::number(s2pd.Solid[znum].pointCloud[0].z * 1000) << endl
						<< "-999999,-999999," << QString::number(s2pd.Solid[znum].pointCloud[0].z * 1000) << endl
						<< "-999999,-999999," << QString::number(s2pd.Solid[znum].pointCloud[0].z * 1000) << endl;
				}
				progressDialog.setValue(znum + 1);
				QApplication::processEvents();
				// 检查是否点击了"取消"按钮
				if (progressDialog.wasCanceled())
				{
					break; // 退出循环
				}
			}
			// 关闭进度提示框
			QApplication::processEvents();
			progressDialog.close();
		}

		file.close();
	}
}

void MainWindow::on_toBMPButton_clicked()
{
	QString folderPath = QFileDialog::getExistingDirectory(this, "选择文件夹", filePath, QFileDialog::ShowDirsOnly);
	QDir folder(folderPath);
	QStringList bmpFilters;
	bmpFilters << "*.bmp"; // 这里可以根据您的需求添加其他BMP文件扩展名

	// 获取目录中的所有BMP文件
	QStringList bmpFiles = folder.entryList(bmpFilters, QDir::Files);

	foreach(const QString &bmpFile, bmpFiles)
	{
		QString BMPfilePath = folder.filePath(bmpFile);
		QFile BMPfile(BMPfilePath);

		if (BMPfile.exists()) {
			BMPfile.remove();
		}
	}

	// 创建进度提示框
	QProgressDialog progressDialog("toBMP...", "取消", 0, s2pd.slicenumber_total);
	progressDialog.setWindowTitle(QString("toBMP"));
	progressDialog.setLabelText(QString("toBMP.."));
	progressDialog.setValue(0);
	progressDialog.setWindowModality(Qt::WindowModal);
	progressDialog.setAutoClose(false);
	progressDialog.setAutoReset(false);
	progressDialog.show();
	QApplication::processEvents();


	QImage Img(BMPlength, BMPwidth, QImage::Format_RGB32);
	QImage Img0(BMPlength, BMPwidth, QImage::Format_RGB32);
	QImage Img1(BMPlength, BMPwidth, QImage::Format_RGB32);
	QImage Img2(BMPlength, BMPwidth, QImage::Format_RGB32);
	QImage Img3(BMPlength, BMPwidth, QImage::Format_RGB32);
	for (int znum = 0; znum < s2pd.slicenumber_total; znum++)
	{
		Img.fill(qRgb(0, 0, 0));
		Img0.fill(qRgb(0, 0, 0));
		Img1.fill(qRgb(0, 0, 0));
		Img2.fill(qRgb(0, 0, 0));
		Img3.fill(qRgb(0, 0, 0));

		for (int pnum = 0; pnum < s2pd.Solid[znum].pointCloud.size(); pnum++)
		{
			Img.setPixel(int(s2pd.Solid[znum].pointCloud[pnum].x / BMPpitchX + BMPlength / 2),
				int(s2pd.Solid[znum].pointCloud[pnum].y / BMPpitchY + BMPwidth / 2), qRgb(255, 255, 255));

		}
		if (ui->rasterCheckBox->isChecked() && s2pd.Solid[znum].pointCloud.size() > 0)
		{
			for (int x = 0; x < BMPlength; x++)
			{
				for (int y = 0; y < BMPwidth; y++)
				{
					if (x % 8 < 4) {
						Img0.setPixel(x, y, Img.pixel(x, y));
					}
					if ((x - 1) % 8 < 4) {
						Img1.setPixel(x, y, Img.pixel(x, y));
					}
					if ((x - 2) % 8 < 4) {
						Img2.setPixel(x, y, Img.pixel(x, y));
					}
					if ((x - 3) % 8 < 4) {
						Img3.setPixel(x, y, Img.pixel(x, y));
					}
				}
			}
			Img0.save(folder.filePath(QString("%1").arg(znum * 4, 4, 10, QChar('0')) + ".bmp"), "BMP");
			Img1.save(folder.filePath(QString("%1").arg(znum * 4 + 1, 4, 10, QChar('0')) + ".bmp"), "BMP");
			Img2.save(folder.filePath(QString("%1").arg(znum * 4 + 2, 4, 10, QChar('0')) + ".bmp"), "BMP");
			Img3.save(folder.filePath(QString("%1").arg(znum * 4 + 3, 4, 10, QChar('0')) + ".bmp"), "BMP");
		}
		else
		{
			// 保存图像为BMP文件
			Img.save(folder.filePath(QString("%1").arg(znum, 4, 10, QChar('0')) + ".bmp"), "BMP");
		}


		progressDialog.setValue(znum + 1);
		QApplication::processEvents();
		// 检查是否点击了"取消"按钮
		if (progressDialog.wasCanceled())
		{
			break; // 退出循环
		}
	}
	// 关闭进度提示框
	QApplication::processEvents();
	progressDialog.close();
	return;

}