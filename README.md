# osg-exercise
注意：在运行工程前需要配置OSG的系统环境及OSG的工程环境。  
配置系统环境：    
　　1) 添加系统变量：OSG_FILE_PATH，变量值为编译好的OSG的data文件夹所在路径；    
　　2) 在系统变量的PATH变量中添加：编译好的OSG的bin文件夹所在路径。    
配置工程环境：  
　　在VS中，右键项目名称，选择“属性”，选择VC++目录，修改包含目录中第一个路径为自己电脑上已经编译好的OSG的include文件夹所在路径，修改库目录中第一个路径为自己电脑上已经编译好的OSG的lib文件夹所在路径。  

若在运行程序时遇到报错“找不到Windows SDK版本10.0.17134.0”则可以进行以下操作：  
　　1）右键单击“解决方案”，选择“重定解决方案目标”。推荐使用此方法。  
　　2）可以修改VS，安装SDK的该版本。此方法较耗时。  

## 0.OSG_0_RunModel  
　　　　![OSG_0_RunModel](OSG_0_RunModel/OSG_0_RunModel.gif)

## 1.OSG_1_NodeTransform  
　　　　![OSG_1_NodeTransform](OSG_1_NodeTransform/OSG_1_NodeTransform.gif)

## 2.OSG_2_NodeSwitch  
　　　　![OSG_2_NodeSwitch](OSG_2_NodeSwitch/OSG_2_NodeSwitch.gif)

## 3.OSG_3_GeometryQuads  
　　　　![OSG_3_GeometryQuads](OSG_3_GeometryQuads/OSG_3_GeometryQuads.gif)

## 4.OSG_4_GeometryHouse  
　　　　![OSG_4_GeometryHouse](OSG_4_GeometryHouse/OSG_4_GeometryHouse.gif)

## 5.OSG_5_GeometryRotatingLine  
　　　　![OSG_5_GeometryRotatingLine](OSG_5_GeometryRotatingLine/OSG_5_GeometryRotatingLine.gif)  
　　　　![OSG_5_GeometryRotatingLine_BreakPoint](OSG_5_GeometryRotatingLine/OSG_5_GeometryRotatingLine_BreakPoint.gif)

## 6.OSG_6_OperatingSimplify  
　　　　![OSG_6_OperatingSimplify](OSG_6_OperatingSimplify/OSG_6_OperatingSimplify.gif)

## 7.OSG_7_OperatingDelaunay  
　　　　![OSG_7_OperatingDelaunay](OSG_7_OperatingDelaunay/OSG_7_OperatingDelaunay.gif)

## 8.OSG_8_RenderClipeNode  
　　　　![OSG_8_RenderClipeNode](OSG_8_RenderClipeNode/OSG_8_RenderClipeNode.gif)  
　　　　![OSG_8_Renderclipnode](OSG_8_RenderClipeNode/OSG_8_Renderclipnode.gif)