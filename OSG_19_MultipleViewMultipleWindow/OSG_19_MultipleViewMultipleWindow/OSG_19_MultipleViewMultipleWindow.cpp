// OSG_19_MultipleViewMultipleWindow.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//视图窗口
osg::ref_ptr<osgViewer::Viewer> MultipleView(osg::ref_ptr<osg::Node> node, int i)
{
	int xoffset = 50;
	int yoffset = 200;

	//设置图形环境特性
	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();
	//两个视图窗口的横坐标位置不同，否则会重叠
	if (i == 1)
	{
		traits->x = xoffset + 0;
	}
	else
	{
		traits->x = xoffset + 600;
	}
	traits->y = yoffset + 0;
	traits->width = 600;
	traits->height = 480;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	
	//创建视图
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	//创建相机
	osg::ref_ptr<osg::Camera> camera = viewer->getCamera();

	//创建图形环境特性
	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());	
	//设置图形环境
	camera->setGraphicsContext(gc.get());

	//设置视口
	camera->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	
	//设置缓冲
	GLenum buffer = traits->doubleBuffer ? GL_BACK : GL_FRONT;
	//设置缓冲区（设置每帧开始绘制时，绘制哪个缓存）
	camera->setDrawBuffer(buffer);
	camera->setReadBuffer(buffer);

	//设置场景数据
	viewer->setSceneData(node.get());

	return viewer.get();
}

int main()
{
	//读取模型，分别作为两个视图的节点
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile("cow.osg");
	osg::ref_ptr<osg::Node> cessna = osgDB::readNodeFile("cessna.osg");

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(cow.get());
	optimizer.optimize(cessna.get());

	//创建两个视图
	osg::ref_ptr<osgViewer::Viewer> viewer1 = MultipleView(cow, 1);
	osg::ref_ptr<osgViewer::Viewer> viewer2 = MultipleView(cessna, 2);

	//创建一个CompositeViewer对象
	osg::ref_ptr<osgViewer::CompositeViewer> viewer = new osgViewer::CompositeViewer();
	//添加视图
	viewer->addView(viewer1.get());
	viewer->addView(viewer2.get());
	viewer->realize();

	return viewer->run();
}