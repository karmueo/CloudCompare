// Example of a plugin action

#include "ccMainAppInterface.h"
#include "ElementPickupAction.h"
#include <ccPointCloud.h>
//PclUtils
#include <sm2cc.h>
#include <cc2sm.h>
#include <PCLConv.h>
#include <pcl/filters/voxel_grid.h>

namespace ElementPickup
{
	// This is an example of an action's method called when the corresponding action
	// is triggered (i.e. the corresponding icon or menu entry is clicked in CC's
	// main interface). You can access most of CC's components (database,
	// 3D views, console, etc.) via the 'appInterface' variable.
	void performElementPickupAction( ccMainAppInterface *appInterface )
	{
		if ( appInterface == nullptr )
		{
			// The application interface should have already been initialized when the plugin is loaded
			Q_ASSERT( false );
			
			return;
		}

		// 判断是否有选择的对象
		if ( appInterface->getSelectedEntities().empty() )
		{
			appInterface->dispToConsole( "[ElementPickup] No object selected!", ccMainAppInterface::ERR_CONSOLE_MESSAGE );
			return;
		}

		// 判断选择的是否为点云
		const ccHObject::Container& selectedEntities = appInterface->getSelectedEntities();
		if ( !appInterface->haveOneSelection() || !selectedEntities.front()->isA(CC_TYPES::POINT_CLOUD))
		{
			appInterface->dispToConsole("Select one cloud!", ccMainAppInterface::ERR_CONSOLE_MESSAGE);
			return;
		}

		auto* ccCloud = dynamic_cast<ccPointCloud*>(selectedEntities.front());
		ccPointCloud* tempCloud = ccCloud->cloneThis(nullptr, true);
		if (!tempCloud)
		{
			return;
		}
//		auto pclCloud = cc2smReader(tempCloud).getAsSM();
		auto pclCloudRaw = cc2smReader(tempCloud).getRawXYZ();

		// 使用PCL进行降采样
		pcl::VoxelGrid<pcl::PointXYZ> sor;
		sor.setInputCloud(pclCloudRaw);
		sor.setLeafSize(1.0f, 1.0f, 1.0f);
		sor.filter(*pclCloudRaw);

		// 将PCL点云转换为CC点云
		PCLCloud out_cloud_sm;
		TO_PCL_CLOUD(*pclCloudRaw, out_cloud_sm);
		if (out_cloud_sm.height * out_cloud_sm.width == 0)
		{
			//cloud is empty
			return;
		}

		ccPointCloud* out_cloud_cc = pcl2cc::Convert(out_cloud_sm);
		if (!out_cloud_cc)
		{
			//conversion failed (not enough memory?)
			return;
		}

		// 将新的点云添加到数据库
		appInterface->addToDB(out_cloud_cc);

		/*** HERE STARTS THE ACTION ***/
	
		// Put your code here
		// --> you may want to start by asking for parameters (with a custom dialog, etc.)
	
		// This is how you can output messages
		// Display a standard message in the console
		appInterface->dispToConsole( "[ExamplePlugin] Hello world!", ccMainAppInterface::STD_CONSOLE_MESSAGE );
		
		// Display a warning message in the console
		appInterface->dispToConsole( "[ExamplePlugin] Warning: example plugin shouldn't be used as is", ccMainAppInterface::WRN_CONSOLE_MESSAGE );
		
		// Display an error message in the console AND pop-up an error box
		appInterface->dispToConsole( "Example plugin shouldn't be used - it doesn't do anything!", ccMainAppInterface::ERR_CONSOLE_MESSAGE );
	
		/*** HERE ENDS THE ACTION ***/
	}
}
