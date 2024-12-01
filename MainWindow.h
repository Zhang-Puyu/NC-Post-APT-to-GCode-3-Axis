#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

#include "qlabel.h"
#include "qthread.h"

#include "ToolpathProcesser.h"
#include "MessageWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindowClass; };
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	
	void openFile();
	void loadFile(const QString& filePath);
	void saveFile();

	void openConfig();
	void saveConfig();

protected:
	void dragEnterEvent(QDragEnterEvent* ev) override;
	void dropEvent(QDropEvent* ev) override;

private:
	Ui::MainWindowClass* ui;

	/// @brief 源文件路径	
	QString m_clsFile;
	/// @brief 后置处理
	ToolpathProcesser* m_processer;
	/// @brief 后置线程
	QThread* m_thread;
	/// @brief 刀轨文件过大
	bool m_bLargeFile = true;

	/// @brief 刀轨文件解析完成
	void onParsed();
	/// @brief 后置处理完成
	/// @param mpfCode 后置后的NC程序代码
	void onProcessed(const QString& mpfCode);

signals:
	void doParseSignal();
	void doProcessSignal();
};
