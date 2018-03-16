#-------------------------------------------------
#
# Project created by QtCreator 2018-03-03T17:55:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sem
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0



HEADERS += \
        src/cs_command.h \
        src/cs_design.h \
        src/cs_model.h \
        src/cs_networker.h \
        src/cs_qheader.h \
        src/dialog_alarm.h \
        src/dialog_form_device_borrow.h \
        src/dialog_form_device_return.h \
        src/dialog_form_device_add.h \
        src/dialog_question.h \
        src/dialog_selector_employee.h \
        src/dialog_signature.h \
        src/dialog_inspector_borrow.h \
        src/dialog_inspector_return.h \
        src/widget_dialog.h \
        src/widget_list_devices.h \
        src/widget_list_employees.h \
        src/widget_list_managements.h \
        src/widget_mainwindow.h \
        src/widget_menu.h \
        src/widget_page.h \
        src/wrapped_widget.h

SOURCES += \
        src/main.cpp \
        src/cs_initializer.cpp \
        src/cs_networker.cpp \
        src/dialog_alarm.cpp \
        src/dialog_form_device_borrow.cpp \
        src/dialog_form_device_return.cpp \
        src/dialog_form_device_add.cpp \
        src/dialog_question.cpp \
        src/dialog_selector_employee.cpp \
        src/dialog_signature.cpp \
        src/dialog_inspector_borrow.cpp \
        src/dialog_inspector_return.cpp \
        src/widget_dialog.cpp \
        src/widget_list_devices.cpp \
        src/widget_list_employees.cpp \
        src/widget_list_managements.cpp \
        src/widget_mainwindow.cpp \
        src/widget_menu.cpp \
        src/widget_page.cpp

FORMS += \
        mainwindow.ui
