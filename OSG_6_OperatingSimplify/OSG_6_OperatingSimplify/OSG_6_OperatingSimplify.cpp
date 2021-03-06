// OSG_6_OperatingSimplify.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


//读取模型  
osg::Node *readModel()
{
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");
	return node.release();
}

//深拷贝并简化新模型  
osg::Node *deepCopy(osg::Node *node)
{
	/*
	创建简化对象
	simplifier(sampleRatio, maxError)
	参数：样本比率、点的误差或边的长度
	样本比率<1 设置点的误差
	样本比率>1 设置边的长度限制
	比率越大，简化越少
	使用的是边塌陷算法
	*/
	float sampleRatio = 0.3f;
	float maxError = 4.0f;
	osgUtil::Simplifier simplifier(sampleRatio, maxError);

	//深拷贝  
	osg::ref_ptr<osg::Node> deepnode = (osg::Node *)(node->clone(osg::CopyOp::DEEP_COPY_ALL));
	//创建一个位置变换节点,将之设置为新位置，将深拷贝的模型移到新位置  
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	pat->setPosition(osg::Vec3(10.0f, 0.0f, 0.0f));
	pat->addChild(deepnode);

	pat->accept(simplifier);

	return pat.release();
}

int main()
{
	//创建一个叶节点对象并添加节点   
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::Node> node1 = readModel();
	osg::ref_ptr<osg::Node> node2 = deepCopy(node1);
	root->addChild(node1);
	root->addChild(node2);

	//优化场景数据  
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	//显示模型  
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	//切换网格模式，方便比较  
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));
	viewer->setSceneData(root.get());
	viewer->realize();

	return viewer->run();
}