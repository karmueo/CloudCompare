//##########################################################################
//#                                                                        #
//#                CLOUDCOMPARE PLUGIN: qElementPickup                      #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#                             COPYRIGHT: XXX                             #
//#                                                                        #
//##########################################################################

#pragma once

#include "ccStdPluginInterface.h"

class qElementPickup : public QObject, public ccStdPluginInterface
{
	Q_OBJECT
	Q_INTERFACES( ccPluginInterface ccStdPluginInterface )

	// info.json文件向加载系统提供有关插件的信息，并显示在插件信息对话框中。
	Q_PLUGIN_METADATA( IID "cccorp.cloudcompare.plugin.qElementPickup" FILE "../info.json" )

public:
	explicit qElementPickup( QObject *parent = nullptr );
	~qElementPickup() override = default;

	// 继承自ccStdPluginInterface
	void onNewSelection( const ccHObject::Container &selectedEntities ) override;
	QList<QAction *> getActions() override;

 protected:
	//! 触发关联操作时调用的插槽
	void doAction();

private:
	/** 可以在插件中添加任意数量的操作。每个动作将对应于专用中的一个图标工具栏和插件菜单中的一个条目。
	**/
	QAction* m_action;

	QAction* m_action2;
};
