// OSG_4_GeometryHouse.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*创建房屋墙体部分
由于房屋为人字顶，因此由10个顶点组成，每个顶点都有对应的法线和纹理坐标，以便正确地实现光照和纹理贴图效果
使用QUAD_STRIP的方式将顶点连接为四边形条带图元
*/
osg::Drawable *createHouseWall()
{
	//创建顶点数组，逆时针添加
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	//添加数据
	vertices->push_back(osg::Vec3(0.0, 0.0, 4.0)); //0
	vertices->push_back(osg::Vec3(0.0, 0.0, 0.0)); //1
	vertices->push_back(osg::Vec3(6.0, 0.0, 4.0)); //2
	vertices->push_back(osg::Vec3(6.0, 0.0, 0.0)); //3
	vertices->push_back(osg::Vec3(6.0, 4.0, 4.0)); //4
	vertices->push_back(osg::Vec3(6.0, 4.0, 0.0)); //5
	vertices->push_back(osg::Vec3(0.0, 4.0, 4.0)); //6
	vertices->push_back(osg::Vec3(0.0, 4.0, 0.0)); //7
	vertices->push_back(osg::Vec3(0.0, 0.0, 4.0)); //8
	vertices->push_back(osg::Vec3(0.0, 0.0, 0.0)); //9
												   
	//创建顶点法线数组
	osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(10);
	//添加数据
	(*normals)[0].set(-0.707, -0.707, 0.0);
	(*normals)[1].set(-0.707, -0.707, 0.0);
	(*normals)[2].set(0.707, -0.707, 0.0);
	(*normals)[3].set(0.707, -0.707, 0.0);
	(*normals)[4].set(0.707, 0.707, 0.0);
	(*normals)[5].set(0.707, 0.707, 0.0);
	(*normals)[6].set(-0.707, 0.707, 0.0);
	(*normals)[7].set(-0.707, 0.707, 0.0);
	(*normals)[8].set(-0.707, -0.707, 0.0);
	(*normals)[9].set(-0.707, -0.707, 0.0);


	//创建纹理坐标
	osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array(10);
	//添加数据
	(*texcoords)[0].set(0.0, 1.0);
	(*texcoords)[1].set(0.0, 0.0);
	(*texcoords)[2].set(0.3, 1.0);
	(*texcoords)[3].set(0.3, .0);
	(*texcoords)[4].set(0.5, 1.0);
	(*texcoords)[5].set(0.5, 0.0);
	(*texcoords)[6].set(0.8, 1.0);
	(*texcoords)[7].set(0.8, 0.0);
	(*texcoords)[8].set(1.0, 1.0);
	(*texcoords)[9].set(1.0, 0.0);

	//创建一个几何对象
	osg::ref_ptr<osg::Geometry> houseWall = new osg::Geometry;
	//设置顶点数据、纹理坐标、法线数组
	houseWall->setVertexArray(vertices.get());
	houseWall->setTexCoordArray(0, texcoords.get());
	houseWall->setNormalArray(normals.get());
	//设置法线的绑定方式为每个属性与一个图元组相绑定，该方法自动设置使用glBegin()/glEnd()的慢速通道进行绘制
	houseWall->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
	//添加图元，多段四边形条带，即一系列四边形
	houseWall->addPrimitiveSet(new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 10));
	//设置纹理贴图
	//C++项目的当前目录为vcproj工程文件目录
	houseWall->getOrCreateStateSet()->setTextureAttributeAndModes(0, new osg::Texture2D(osgDB::readImageFile("../wall.bmp")));

	return houseWall.release();
}

/*创建人字顶部分
人字顶由6个顶点组成
使用颜色数组替代纹理，表达顶面的绘制效果
*/
osg::Drawable *createHouseRoof()
{
	//创建顶点数组，逆时针添加
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	//添加数据
	vertices->push_back(osg::Vec3(-0.2, -0.5, 3.5)); //0
	vertices->push_back(osg::Vec3(6.2, -0.5, 3.5)); //1
	vertices->push_back(osg::Vec3(0.8, 2.0, 6.0)); //2
	vertices->push_back(osg::Vec3(5.2, 2.0, 6.0)); //3
	vertices->push_back(osg::Vec3(-0.2, 4.5, 3.5)); //4
	vertices->push_back(osg::Vec3(6.2, 4.5, 3.5)); //5

	//绘图基元为多段四边形条带
	osg::ref_ptr<osg::DrawArrays> roof = new osg::DrawArrays(osg::DrawArrays::QUAD_STRIP, 0, 6);
	//绘图基元为三角形
	osg::ref_ptr<osg::DrawElementsUInt> roofSide = new osg::DrawElementsUInt(osg::DrawElementsUInt::TRIANGLES, 6);
	(*roofSide)[0] = 0;
	(*roofSide)[1] = 2;
	(*roofSide)[2] = 4;
	(*roofSide)[3] = 5;
	(*roofSide)[4] = 3;
	(*roofSide)[5] = 1;

	//创建屋顶颜色数组
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	//添加数据
	colors->push_back(osg::Vec4(0.25, 0.0, 0.0, 1.0));

	//创建一个几何体对象
	osg::ref_ptr<osg::Geometry> houseRoof = new osg::Geometry;
	//设置顶点数据、颜色数组
	houseRoof->setVertexArray(vertices.get());
	houseRoof->setColorArray(colors.get());
	//设置颜色的绑定方式为一个属性与所有顶点绑定
	houseRoof->setColorBinding(osg::Geometry::BIND_OVERALL);
	//添加图元
	houseRoof->addPrimitiveSet(roof.get());
	houseRoof->addPrimitiveSet(roofSide.get());
	//由于顶面的法线计算比较复杂，这里使用OSG自带的快速法线生成工具osgUtil::SmoothingVisito
	osgUtil::SmoothingVisitor smv;
	smv.smooth(*houseRoof);
	return houseRoof.release();
}


int main(int argc, char **argv)
{
	//将房屋和墙体整合到一个叶节点中进行渲染
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(createHouseWall());
	geode->addDrawable(createHouseRoof());

	osgViewer::Viewer viewer;

	viewer.setSceneData(geode.get());
	return viewer.run();
}

