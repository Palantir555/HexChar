
#Copyright 2013 Juan Carlos Jiménez Caballero -- www.jcjc-dev.com
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
#   Unless required by applicable law or agreed to in writing, software
#   distributed under the License is distributed on an "AS IS" BASIS,
#   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#   See the License for the specific language governing permissions and
#   limitations under the License.


ICON = resources/H_icon.icns

TEMPLATE = app
TARGET = 
DEPENDPATH += .

INCLUDEPATH += /opt/local/include

SOURCES += main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h

RESOURCES += \
    resources/resources.qrc

