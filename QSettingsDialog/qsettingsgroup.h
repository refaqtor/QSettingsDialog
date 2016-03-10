#ifndef QSETTINGSGROUP_H
#define QSETTINGSGROUP_H

#include "qsettingsdialog_global.h"
#include <QString>
class QSettingsEntry;
class QGroupBox;
class QFormLayout;

class QSETTINGSDIALOGSHARED_EXPORT QSettingsGroup
{
	friend class QSettingsSection;

public:
	bool isActivated() const;

	QString name() const;
	bool isOptional() const;

	void setName(const QString &name);
	void setOptional(bool optional);

	QList<QSettingsEntry*> entries() const;
	QSettingsEntry *entryAt(int index) const;
	int entryIndex(QSettingsEntry *entry) const;

	void insertEntry(int index, QSettingsEntry *entry);
	inline void addEntry(QSettingsEntry *entry) {
		this->insertEntry(this->entrs.size(), entry);
	}

	void deleteEntry(int index);
	bool deleteEntry(QSettingsEntry *entry);

	void moveEntry(int from, int to);

private:
	QGroupBox *box;
	QWidget *widget;
	QFormLayout *layout;

	QList<QSettingsEntry *> entrs;

	QSettingsGroup(QGroupBox *box);
	QSettingsGroup(QWidget *widget);
	~QSettingsGroup();
};

#endif // QSETTINGSGROUP_H
