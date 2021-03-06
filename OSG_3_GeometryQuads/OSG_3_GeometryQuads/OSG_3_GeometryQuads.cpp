// OSG_3_GeometryQuads.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"


/*绘制并渲染几何体的主要步骤：
1.创建各种向量数据，如顶点、纹理坐标、颜色、法线。顶点数据按照逆时针顺序添加，以确保背面剔除的正确
2.实例化几何对象osg::Geometry，设置顶点坐标数组、纹理坐标数组、颜色数组、法线数组、绑定方式和数据解析
3.加入叶节点绘制并渲染
*/

/*向量数据的实现函数
void setVertexArray(Array *array) //设置顶点数组
void setVertexData(const ArrayData &arrayData) //设置顶点数组数据
void setVertexIndices(IndexArray *array) //设置顶点索引数组
void setNormalArray(Array *array) //设置法线数组
void setNormalData(const ArrayData &arrayData) //设置法线数组数据
void setNormalIndices(IndexArray *array) //设置法线索引数组
void setCorlorArray(Array *array) //设置颜色数组
void setCorlorData(const ArrayData &arrayData) //设置颜色数组数据
void setCorlorIndices(IndexArray *array) //设置颜色索引数组
void setTexCoordArray(unsigned int unit, Array *) //设置纹理坐标数组，参数纹理单元 / 纹理坐标数组
void setTexCoordData(unsigned int index, const ArrayData &arrayData) //设置纹理坐标数组数据，参数纹理单元 / 纹理坐标数组数据
vlid setTexCoordIndices(unsigned int unit, IndexArray *) //设置纹理坐标索引数组，参数纹理单元 / 纹理索引坐标数组
*/
osg::ref_ptr<osg::Node> createQuad()
{
	//创建一个叶节点对象
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	//创建一个几何体对象
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	//创建顶点数组，注意顶点的添加顺序是逆时针的
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	//添加数据
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	//设置顶点数据setVertexArray(Array *array)
	geom->setVertexArray(v.get());

	//创建纹理数组，必须和顶点数组的大小相同
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
	//添加数据
	vt->push_back(osg::Vec2(0.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 1.0f));
	vt->push_back(osg::Vec2(0.0f, 1.0f));
	//设置纹理坐标数组setTexCoordArray(unsigned int unit, Array *)参数纹理单元/纹理坐标数组
	geom->setTexCoordArray(0, vt.get());

	//数据绑定：法线、颜色，绑定方式为：
	//BIND_OFF不启动用绑定
	//BIND_OVERALL绑定全部顶点
	//BIND_PER_PRIMITIVE_SET单个绘图基元绑定,每个属性与一个图元组绑定，一个几何体可能由多个图元组构成，如一个复杂多边形可能由一个或多个三角条带图元组以及一个或多个标示边界的线条带图元组组成
	//BIND_PER_PRIMITIVE单个独立的绘图基元绑定，OSG采用glBegin()/glEnd()函数进行渲染，因为该绑定方式为每个独立的几何图元设置一种绑定方式
	//BIND_PER_VERTIE单个顶点绑定，属性顶点一一对应，最常见

	//创建颜色数组
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	//添加数据
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	//设置颜色数组setColorArray(Array *array)
	geom->setColorArray(vc.get());
	//设置颜色的绑定方式setColorBinding(AttributeBinding ab)为单个顶点
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//创建法线数组
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	//添加法线
	nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
	//设置法线数组setNormalArray(Array *array)
	geom->setNormalArray(nc.get());
	//设置法线的绑定方式setNormalBinding(AttributeBinding ab)为全部顶点
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	//添加图元，绘制基元为四边形
	//数据解析，即指定向量数据和绑定方式后，指定渲染几何体的方式，不同方式渲染出的图形不同，即时效果相同，可能面数或内部机制等也有区别，函数为：
	//bool addPrimitiveSet(PrimitiveSet *primitiveset)参数说明：osg::PrimitiveSet是无法初始化的虚基类，因此主要调用它的子类指定数据渲染，最常用为osg::DrawArrays
	//osg::DrawArrays(GLenum mode, GLint first, GLsizei count)，指定绘制时从每一个预置的顶点属性数组中读取连续数据，以构成mode类型的几何图元序列，起始为第first个元素，共使用count个元素进行构建
	//参数为指定的绘图基元、绘制几何体的第一个顶点数在指定顶点的位置数、使用的顶点的总数
	//PrimitiveSet类继承自osg::Object虚基类，但不具备一般一般场景中的特性，PrimitiveSet类主要封装了OpenGL的绘图基元，常见绘图基元如下
	//POINTS点/LINES线/LINE_STRIP多线段/LINE_LOOP封闭线
	//TRIANGLES一系列三角形(不共顶点)/TRIANGLE_STRIP一系列三角形(共用后面两个顶点)/TRIANGLE_FAN一系列三角形，顶点顺序与上一条语句绘制的三角形不同
	//QUADS四边形/QUAD_STRIP一系列四边形/POLYGON多边形
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	//添加到叶节点
	geode->addDrawable(geom.get());

	return geode.get();
}

int main(int argc, char **argv)
{
	//方法1：在智能指针中创建viewer，使用它的方法用"->"
	//创建Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	//添加到场景
	root->addChild(createQuad());

	//优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();

	return 0;

	//方法2：直接创建viewer，使用它的方法用"."
	/*osg::ref_ptr<osg::Group> root = new osg::Group();
	root->addChild(createQuad());

	osgViewer::Viewer viewer;

	viewer.setSceneData(root.get());
	return viewer.run();*/
}

