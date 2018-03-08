#ifndef COMMANDER_H
#define COMMANDER_H

#include <QObject>

class Settings;
class Commander : public QObject
{
	Q_OBJECT
public:
	static Commander* getInstance()
	{
		if (m_instance == nullptr)
			m_instance = new Commander();
		return m_instance;
	}

	enum SNS_TYPE { NONE, EMAIL, KAKAO, FACEBOOK };

	

private:
	Commander(QObject *parent = NULL);
	~Commander();
	static Commander* m_instance;

};

#endif // COMMANDER_H
