#include "cs_commander.h"
#include <QDebug>

Commander* Commander::m_instance = nullptr;
Commander::Commander(QObject *parent) : QObject(parent)
{
	
}
Commander::~Commander()
{
	//delete m_model;
}
