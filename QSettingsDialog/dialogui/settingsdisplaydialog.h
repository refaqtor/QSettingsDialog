#ifndef SETTINGSDISPLAYDIALOG_H
#define SETTINGSDISPLAYDIALOG_H

#include <QDialog>
#include <QStyledItemDelegate>
#include <QAbstractButton>
#include <QProgressDialog>
#include <QFormLayout>
#include <functional>
#include "qsettingswidgetdialogengine.h"
#include "containerelements.h"
#include "qsettingsgroupwidget.h"
class SettingsEngine;

namespace Ui {
	class SettingsDisplayDialog;
}

class CategoryItemDelegate : public QStyledItemDelegate
{
public:
	CategoryItemDelegate(std::function<void(int)> updateFunc,
						 const QSize &iconSize,
						 int layoutSpacing,
						 QObject *parent = Q_NULLPTR);

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
private:
	QSize iconSize;
	std::function<void(int)> updateFunc;
};

class SettingsDisplayDialog : public QDialog, public QSettingsDisplayInstance
{
	Q_OBJECT

public:
	explicit SettingsDisplayDialog(QSettingsWidgetDialogEngine *engine);
	~SettingsDisplayDialog();

	void setParentWindow(QWidget *parent) override;
	void setParentWindow(QWindow *parent) override;
	void createUi(const QSharedPointer<SettingsRoot> &elementRoot) override;

public slots:
	void open() override;
	int exec() override;

signals:
	void saved(bool closed) final;
	void resetted() final;
	void canceled() final;

protected:
	void showEvent(QShowEvent *ev) override;

private slots:
	void startSaving(bool isApply);
	void startResetting();

	void engineFinished(int errorCount);
	void completeAbort();

	void resetListSize();
	void updateWidth(int width);

	void buttonBoxClicked(QAbstractButton *button);
	void on_filterLineEdit_textChanged(const QString &searchText);

private:
	enum OperationMode {
		Idle,
		Load,
		Save,
		Apply,
		Reset
	};

	QSettingsWidgetDialogEngine *dialogEngine;
	SettingsEngine *engine;

	Ui::SettingsDisplayDialog *ui;	
	CategoryItemDelegate *delegate;
	int maxWidthBase;

	OperationMode currentMode;
	QProgressDialog *workingDialog;

	int calcSpacing(Qt::Orientation orientation);

	void createCategory(const QSharedPointer<SettingsCategory> &category);
	void createSection(const QSharedPointer<SettingsSection> &section, QTabWidget *tabWidget);
	void createGroup(const QSharedPointer<SettingsGroup> &group, QWidget *contentWidget, QFormLayout *layout);
	void createEntry(const QSharedPointer<QSettingsEntry> &entry, QWidget *sectionWidget, QFormLayout *layout);
	void createEntry(const QSharedPointer<QSettingsEntry> &entry, QSettingsGroupWidgetBase *group);

	QWidget *createErrorWidget(QWidget *parent);

	void searchInDialog(const QRegularExpression &regex);
	bool searchInCategory(const QRegularExpression &regex, QTabWidget *tab);
	bool searchInSection(const QRegularExpression &regex, QWidget *contentWidget);
	bool searchInGroup(const QRegularExpression &regex, QSettingsGroupWidgetBase *groupWidget);
	bool searchInEntry(const QRegularExpression &regex, QWidget *label, QSettingsWidgetBase *content);
};

#endif // SETTINGSDISPLAYDIALOG_H
