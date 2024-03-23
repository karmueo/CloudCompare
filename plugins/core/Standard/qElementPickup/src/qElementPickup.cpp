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
#include <QtGui>

#include "qElementPickup.h"


//	- 将Qt资源路径传递到info.json文件（来自qElementPickup.qrc文件）
qElementPickup::qElementPickup( QObject *parent )
	: QObject( parent )
	, ccStdPluginInterface( ":/CC/plugin/qElementPickup/info.json" )
	, m_action( nullptr )
{
}

// 此方法应启用或禁用插件操作
// 取决于当前选定的实体（“选定实体”）。
void qElementPickup::onNewSelection( const ccHObject::Container &selectedEntities )
{
	if ( m_action == nullptr )
	{
		return;
	}
	
	// 例如-仅当选择了某个内容时才启用我们的操作。
	m_action->setEnabled( !selectedEntities.empty() );
}

// 此方法返回插件可以执行的所有“操作”。
// 加载插件时，getActions（）将只调用一次。
QList<QAction *> qElementPickup::getActions()
{
	// 默认操作（如果尚未创建，则此时执行）
	if ( !m_action )
	{
		// 这里使用默认的插件名称、描述和图标，
		m_action = new QAction( getName(), this );
		m_action->setToolTip( getDescription() );
		m_action->setIcon( getIcon() );
		
		// 连接信号
		connect( m_action, &QAction::triggered, this, &qElementPickup::doAction );
	}

	return { m_action };
}

/**
 * 在CC的主界面中点击相应的图标或菜单项调用的动作方法。可以通过“m_app”变量访问CC的大部分组件（数据库、三维视图、控制台等）。
 * 此方法将在主线程中调用，因此可以安全地访问CC的所有组件。
 */
void qElementPickup::doAction()
{
	if ( m_app == nullptr )
	{
		// 加载插件时，应用程序接口应该已经初始化
		Q_ASSERT( false );

		return;
	}

	/*** 这里开始具体处理 ***/

	// TODO: Put your code here
	// --> 比如获取参数（使用自定义对话框等）

	// 输出消息的方式
	// 在控制台中显示标准消息
	m_app->dispToConsole( "[qElementPickup] Hello qElementPickup!", ccMainAppInterface::STD_CONSOLE_MESSAGE );

	// 在控制台中显示警告消息
	m_app->dispToConsole( "[qElementPickup] Warning: qElementPickup plugin Warning.", ccMainAppInterface::WRN_CONSOLE_MESSAGE );

	// 在控制台中显示错误消息并弹出错误框
	m_app->dispToConsole( "qElementPickup doesn't do anything!", ccMainAppInterface::ERR_CONSOLE_MESSAGE );

	/*** 结束处理 ***/
}
