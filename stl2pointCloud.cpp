﻿//#include<pcl/visualization/cloud_viewer.h>
#include<iostream>
//#include<pcl/io/io.h>
//#include<pcl/io/pcd_io.h>
//#include<pcl/io/ply_io.h>
//#include<pcl/point_types.h>
#include "stl2pointCloud.h"
#include <cmath>

#include <QProgressDialog>
#include <QEventLoop>
#include <QApplication>

//Stl2pointCould createPcd()
//{
//	Stl2pointCould s2pd = Stl2pointCould();
//	s2pd.stlstrpath = "D:\\File\\ModelAndDrawing\\ball.STL";
//	s2pd.pcdstrpath = "cube.pcd";
//	s2pd.txtstrpath = "cube.txt";
//	s2pd.mPrecisionZ = 0.2;
//	s2pd.mPrecisionX = 0.2;
//	s2pd.mPrecisionY = 0.2;
//	s2pd.allowError = 0.01;
//
//	bool flag = s2pd.readStl();
//	cout << "FacetArray.size()=" << s2pd.FacetArray.size() << endl;
//	for (int i = 0; i < s2pd.FacetArray.size(); i++)
//	{
//		cout << "FacetArray[" << i << "]\t("
//			<< s2pd.FacetArray[i].i << "," << s2pd.FacetArray[i].j << "," << s2pd.FacetArray[i].k << ")\t\t"
//			<< "P1(" << s2pd.FacetArray[i].P1.x << "," << s2pd.FacetArray[i].P1.y << "," << s2pd.FacetArray[i].P1.z << ")\t"
//			<< "P2(" << s2pd.FacetArray[i].P2.x << "," << s2pd.FacetArray[i].P2.y << "," << s2pd.FacetArray[i].P2.z << ")\t"
//			<< "P3(" << s2pd.FacetArray[i].P3.x << "," << s2pd.FacetArray[i].P3.y << "," << s2pd.FacetArray[i].P3.z << ")\t"
//			<< endl;
//	}
//	s2pd.Slice_STL();
//	//LayerType *pl = s2pd.HeadLayer;
//	//for (int znum = 0; znum < s2pd.slicenumber_total; znum++)
//	//{
//	//	cout << "z = " << (s2pd.zmin + znum * s2pd.mPrecisionZ) << endl;
//	//	cout << "pl->Contour.size()=" << pl->Contour.size() << endl;
//	//	for (int j = 0; j < pl->Contour.size(); j++)
//	//	{
//	//		cout << "\t head(" << pl->Contour[j].head.x << "," << pl->Contour[j].head.y << "," << pl->Contour[j].head.z << ")\t"
//	//			<< "\t tail(" << pl->Contour[j].tail.x << "," << pl->Contour[j].tail.y << "," << pl->Contour[j].tail.z << ")\t"
//	//			<< endl;
//	//	}
//	//	pl = pl->pLayer;
//	//}
//	s2pd.find_closedContours();
//	//pl = s2pd.HeadLayer;
//	//for (long znum = 0; znum < s2pd.slicenumber_total; znum++)
//	//{
//	//	cout << "z = " << (s2pd.zmin + znum * s2pd.mPrecisionZ) << endl;
//	//	cout << "pl->closedContours.size() = " << pl->closedContours.size() << endl;
//	//	cout << endl;
//	//	pl = pl->pLayer;
//	//}
//	s2pd.to3DMatrix();
//	cout << "s2pd.index.size() = " << s2pd.index.size() << endl;
//
//
//	pcl::PointCloud<pcl::PointXYZ> cloud;
//	// 创建点云
//	cloud.width = s2pd.index.size();
//	cloud.height = 1;
//	cloud.is_dense = false;
//	cloud.points.resize(cloud.width * cloud.height);
//
//	for (size_t i = 0; i < cloud.points.size(); i++)
//	{
//		cloud.points[i].x = s2pd.xx[i];
//		cloud.points[i].y = s2pd.yy[i];
//		cloud.points[i].z = s2pd.zz[i];
//	}
//	pcl::io::savePCDFileASCII(s2pd.pcdstrpath, cloud);
//
//	ofstream txtFile;
//	txtFile.open(s2pd.txtstrpath, ios::out);
//	for (size_t i = 0; i < cloud.points.size(); i++)
//	{
//		txtFile << s2pd.xx[i] * 1000 << "," << s2pd.yy[i] * 1000 << "," << s2pd.zz[i] * 1000 << endl;
//	}
//	txtFile.close();
//
//	return s2pd;
//}
// 读取STL文件，并将三角片信息写入FacetArray，再调用Slice_ResortFacet()对三角片三顶点排序
bool Stl2pointCould::readStl()
{
	FILE *pFile;
	FacetType facet_buffer;

	FacetArray.clear();

	const char *path = nullptr;
	path = stlstrpath.c_str();
	pFile = fopen(path, "rb");
	if (pFile == NULL)
	{
		cout << "pFile == NULL" << endl;
		return false;
	}
	else
	{
		cout << "pFile != NULL" << endl;
	}

	fseek(pFile, 80, SEEK_SET);                  // 跳过文件头
	fread(&facetnumber, sizeof(char), 4, pFile); // 读取4个byte表示的三角形平面数

	for (int i = 1; i <= facetnumber; i++)
	{
		fread(&facet_buffer, sizeof(facet_buffer), 1, pFile);

		xmin = GetMin(facet_buffer.P1.x, facet_buffer.P2.x, facet_buffer.P3.x, xmin);
		ymin = GetMin(facet_buffer.P1.y, facet_buffer.P2.y, facet_buffer.P3.y, ymin);
		zmin = GetMin(facet_buffer.P1.z, facet_buffer.P2.z, facet_buffer.P3.z, zmin);

		xmax = GetMax(facet_buffer.P1.x, facet_buffer.P2.x, facet_buffer.P3.x, xmax);
		ymax = GetMax(facet_buffer.P1.y, facet_buffer.P2.y, facet_buffer.P3.y, ymax);
		zmax = GetMax(facet_buffer.P1.z, facet_buffer.P2.z, facet_buffer.P3.z, zmax); // 获取各方向的最小值和最大值

		FacetArray.push_back(facet_buffer); // 加入三角形平面链表
		fseek(pFile, 2, SEEK_CUR);          // 跳过两个三角形平面属性描述
	}
	Slice_ResortFacet();

	fclose(pFile);

	return true;
}

// 返回四个参数中的最小值
double Stl2pointCould::GetMin(double x1, double x2, double x3, double min)
{
	double x;
	x = x1 < x2 ? x1 : x2;
	x = x < x3 ? x : x3;
	x = x < min ? x : min;
	return x;
}
// 返回四个参数中的最大值
double Stl2pointCould::GetMax(double x1, double x2, double x3, double max)
{
	double x;
	x = x1 > x2 ? x1 : x2;
	x = x > x3 ? x : x3;
	x = x > max ? x : max;
	return x;
}
// stl实体坐标排序，使P1.z>P2.z>P3.z
void Stl2pointCould::Slice_ResortFacet(void)
{

	FacetType pfacet;
	for (int i = 0; i < FacetArray.size(); i++)
	{
		pfacet.i = FacetArray[i].i;
		pfacet.j = FacetArray[i].j;
		pfacet.k = FacetArray[i].k;

		pfacet.P1.x = FacetArray[i].P1.x;
		pfacet.P1.y = FacetArray[i].P1.y;
		pfacet.P1.z = FacetArray[i].P1.z;

		pfacet.P2.x = FacetArray[i].P2.x;
		pfacet.P2.y = FacetArray[i].P2.y;
		pfacet.P2.z = FacetArray[i].P2.z;

		pfacet.P3.x = FacetArray[i].P3.x;
		pfacet.P3.y = FacetArray[i].P3.y;
		pfacet.P3.z = FacetArray[i].P3.z;

		pfacet = Orderfacet(pfacet);
		FacetArray[i] = pfacet;
	}
}
// Slice_ResortFacet()坐标排序的子函数，使P1.z>P2.z>P3.z
FacetType Stl2pointCould::Orderfacet(FacetType facet)
{
	VertexType temp; // 定义一个临时点

	if (facet.P1.z < facet.P2.z)
	{
		temp = facet.P1;
		facet.P1 = facet.P2;
		facet.P2 = temp;
	}

	if (facet.P1.z < facet.P3.z)
	{
		temp = facet.P1;
		facet.P1 = facet.P3;
		facet.P3 = temp;
	}

	if (facet.P2.z < facet.P3.z)
	{
		temp = facet.P2;
		facet.P2 = facet.P3;
		facet.P3 = temp;
	}
	return facet;
}

// 对STL实体分片，获得每层轮廓线段集，写入HeadLayer链表
void Stl2pointCould::Slice_STL(void)
{
	double zi;
	bool outflag;

	LayerType *pl, *pl1; // 定义指向层结构的指针
	pl = new LayerType;
	pl1 = pl;
	LayerType layer;
	FacetType tempf;

	Solid.clear();

	slicenumber_total = int((zmax - zmin) / mPrecisionZ) + 1;

	zi = zmin; // 分层面zt从最下面开始


	// 创建进度提示框
	QProgressDialog progressDialog("Slice_STL", "取消", 0, slicenumber_total);
	progressDialog.setWindowTitle(QString("Slice_STL"));
	progressDialog.setLabelText(QString("Slice_STL.."));
	progressDialog.setValue(0);
	progressDialog.setWindowModality(Qt::WindowModal);
	progressDialog.setAutoClose(false);
	progressDialog.setAutoReset(false);
	progressDialog.show();
	QApplication::processEvents();

	for (long znum = 0; znum < slicenumber_total; znum++)
	{
		VectorType tempv, Htempv; // 定义一个直线类型
		vector<VectorType> tempc, Htempc; //交线集合类型
		for (int fnum = 0; fnum < FacetArray.size(); fnum++)
		{
			// 三角片三顶点都在zt分层面，取三角片
			if ((fabs(FacetArray[fnum].P1.z - zi) <= allowError) && (fabs(FacetArray[fnum].P3.z - zi) <= allowError))
			{
				tempf = FacetArray[fnum];
				tempf.P1.z = zi;
				tempf.P2.z = zi;
				tempf.P3.z = zi;
				layer.Hatch.push_back(FacetArray[fnum]);
			}
			// P3不在zt,P1P2在zt，取P1-P2边线
			else if ((fabs(FacetArray[fnum].P1.z - zi) <= allowError) && (fabs(FacetArray[fnum].P2.z - zi) <= allowError))
			{
				tempv.head = FacetArray[fnum].P1;
				tempv.tail = FacetArray[fnum].P2;
				tempv.head.z = zi;
				tempv.tail.z = zi;
				if (!isRepeatLine(tempv, tempc))
					tempc.push_back(tempv);
			}
			// P1不在zt,P2P3在zt，取P2-P3边线
			else if ((fabs(FacetArray[fnum].P2.z - zi) <= allowError) && (fabs(FacetArray[fnum].P3.z - zi) <= allowError))
			{
				tempv.head = FacetArray[fnum].P2;
				tempv.tail = FacetArray[fnum].P3;
				tempv.head.z = zi;
				tempv.tail.z = zi;
				if (!isRepeatLine(tempv, tempc))
					tempc.push_back(tempv);
			}
			// 仅P2在zt，即P1在上，P3在下，取交线
			else if ((fabs(FacetArray[fnum].P2.z - zi) <= allowError))
			{
				tempv.head = FacetArray[fnum].P2;
				tempv.tail = IntersectLine(FacetArray[fnum].P1, FacetArray[fnum].P3, zi);
				tempv.head.z = zi;
				tempv.tail.z = zi;
				if (!isRepeatLine(tempv, tempc))
					tempc.push_back(tempv);
			}
			// P1P2在zt上，P3在zt下，取交线
			else if ((FacetArray[fnum].P2.z - zi > allowError) && (FacetArray[fnum].P3.z - zi < -allowError))
			{
				tempv.head = IntersectLine(FacetArray[fnum].P1, FacetArray[fnum].P3, zi);
				tempv.tail = IntersectLine(FacetArray[fnum].P2, FacetArray[fnum].P3, zi);
				tempv.head.z = zi;
				tempv.tail.z = zi;
				if (!isRepeatLine(tempv, tempc))
					tempc.push_back(tempv);
			}
			// P1在zt上，P2P3在zt下，取交线
			else if ((FacetArray[fnum].P1.z - zi > allowError) && (FacetArray[fnum].P2.z - zi < -allowError))
			{
				tempv.head = IntersectLine(FacetArray[fnum].P1, FacetArray[fnum].P2, zi);
				tempv.tail = IntersectLine(FacetArray[fnum].P3, FacetArray[fnum].P1, zi);
				tempv.head.z = zi;
				tempv.tail.z = zi;
				if (!isRepeatLine(tempv, tempc))
					tempc.push_back(tempv);
			}
		}
		for (int cnum = 0; cnum < tempc.size(); cnum++)
		{
			if (!isRepeatLine(tempc[cnum], Htempc))
				layer.Contour.push_back(tempc[cnum]);
		}
		zi += mPrecisionZ;
		//layer.pLayer = new LayerType;
		//pl = layer.pLayer;

		Solid.push_back(layer);
		layer.Contour.clear();
		layer.Hatch.clear();

		progressDialog.setValue(znum + 1);
		QApplication::processEvents();
		// 检查是否点击了"取消"按钮
		if (progressDialog.wasCanceled())
		{
			break; // 退出循环
		}
	}
	// 关闭进度提示框
	QApplication::processEvents();
	progressDialog.close();
	//pl = NULL;
	//HeadLayer = pl1;
}

// 判断轮廓线段v是否与线段集中线段重复
bool Stl2pointCould::isRepeatLine(VectorType v, vector<VectorType> vec_v)
{
	bool isRepeat = false;

	for (int i = 0; i < vec_v.size(); i++)
	{
		if ((distPP(v.head, vec_v[i].head) < allowError) && (distPP(v.tail, vec_v[i].tail) < allowError))
		{
			isRepeat = true;
			break;
		}
		if ((distPP(v.tail, vec_v[i].head) < allowError) && (distPP(v.head, vec_v[i].tail) < allowError))
		{
			isRepeat = true;
			break;
		}
	}
	return isRepeat;
}

// 返回p1,p2两点距离
double Stl2pointCould::distPP(VertexType p1, VertexType p2)
{
	double d;
	d = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y) + (p1.z - p2.z) * (p1.z - p2.z);
	d = sqrt(d);
	return d;
}

// 判断p1，p2两点是否重合
bool Stl2pointCould::isCoincident(VertexType p1, VertexType p2)
{
	if (distPP(p1, p2) <= allowError)
		return true;
	else
		return false;
}

// 判断起始点是否重复
bool Stl2pointCould::isRepeatHead(VertexType head, vector<PointSet> cc_v)
{
	if (cc_v.size() == 0)
		return false;
	for (long i = 0; i < cc_v.size(); i++)
	{
		vector<VertexType> points_buffer = cc_v[i].points;
		for (long j = 0; j < points_buffer.size(); j++)
		{
			if (isCoincident(head, points_buffer[j]))
				return true;
		}
	}
	return false;
}

// 求p1，p2连线与zt面的交点
VertexType Stl2pointCould::IntersectLine(VertexType p1, VertexType p2, double zt)
{
	VertexType p;
	if (p1.z != p2.z)
	{
		p.x = (zt * (p1.x - p2.x) + p2.x * p1.z - p1.x * p2.z) / (p1.z - p2.z);
		p.y = (zt * (p1.y - p2.y) + p2.y * p1.z - p1.y * p2.z) / (p1.z - p2.z);
		p.z = zt;
		return p;
	}
	return p1;
}

void Stl2pointCould::find_closedContours(void)
{
	LayerType *pl = HeadLayer;
	PointSet cc_buffer;
	

	// 创建进度提示框
	QProgressDialog progressDialog("find_closedContours", "取消", 0, slicenumber_total);
	progressDialog.setWindowTitle(QString("find_closedContours"));
	progressDialog.setLabelText(QString("find_closedContours.."));
	progressDialog.setValue(0);
	progressDialog.setWindowModality(Qt::WindowModal);
	progressDialog.setAutoClose(false);
	progressDialog.setAutoReset(false);
	progressDialog.show();
	QApplication::processEvents();

	for (long znum = 0; znum < slicenumber_total; znum++)
	{
		ccs_buffer.clear();
		for (int cnum = 0; cnum < Solid[znum].Contour.size(); cnum++)
		{
			// 寻找新的封闭曲线起始点
			if (!isRepeatHead(Solid[znum].Contour[cnum].head, ccs_buffer))
			{
				vector<VectorType> Contour_buffer = Solid[znum].Contour;
				cc_buffer.points.clear();
				cc_buffer.points.push_back(Solid[znum].Contour[cnum].head);
				Contour_buffer.erase(Contour_buffer.begin() + cnum);
				// 递归寻找经过起始点的所有封闭曲线，达到封闭条件将点集写入ccs_buffer
				find_layer_closedContours(Solid[znum].Contour[cnum].head, Solid[znum].Contour[cnum].tail, Contour_buffer, cc_buffer);
				int size = ccs_buffer.size();
			}
			// 寻找新的封闭曲线起始点
			else if (!isRepeatHead(Solid[znum].Contour[cnum].tail, ccs_buffer))
			{
				vector<VectorType> Contour_buffer = Solid[znum].Contour;
				cc_buffer.points.clear();
				cc_buffer.points.push_back(Solid[znum].Contour[cnum].tail);
				Contour_buffer.erase(Contour_buffer.begin() + cnum);
				// 递归寻找经过起始点的所有封闭曲线，达到封闭条件将点集写入ccs_buffer
				find_layer_closedContours(Solid[znum].Contour[cnum].tail, Solid[znum].Contour[cnum].head, Contour_buffer, cc_buffer);
				int size = ccs_buffer.size();
			}
		}
		ccs_buffer = removeInnerContours(ccs_buffer);
		for (int ccnum = 0; ccnum < ccs_buffer.size(); ccnum++)
		{
			removeIntermediatePoints(ccs_buffer[ccnum]);
		}

		Solid[znum].closedContours.clear();
		Solid[znum].closedContours.swap(ccs_buffer);

		progressDialog.setValue(znum + 1);
		QApplication::processEvents();
		// 检查是否点击了"取消"按钮
		if (progressDialog.wasCanceled())
		{
			break; // 退出循环
		}
	}
	// 关闭进度提示框
	QApplication::processEvents();
	progressDialog.close();
}


// 递归寻找经过起始点的所有封闭曲线，达到封闭条件将点集写入ccs_buffer
void Stl2pointCould::find_layer_closedContours(VertexType head, VertexType tail, vector<VectorType> vec_v, PointSet cc_buffer)
{
	// 判断达到封闭条件
	if (isCoincident(tail, head))
	{
		// 将点集写入ccs_buffer
		ccs_buffer.push_back(cc_buffer);
		return;
	}
	// 根据当前曲线结尾点，遍历寻找能够连入曲线的轮廓线段
	for (int i = 0; i < vec_v.size(); i++)
	{
		// 判断轮廓线段能否连入曲线
		if (isCoincident(tail, vec_v[i].head))
		{
			VertexType tail_next;
			vector<VectorType> vec_v_next;
			PointSet cc_buffer_next;
			tail_next = vec_v[i].tail;
			vec_v_next = vec_v;
			// 从轮廓线段集中移除已连入曲线的线段
			vec_v_next.erase(vec_v_next.begin() + i);
			cc_buffer_next = cc_buffer;
			cc_buffer_next.points.push_back(vec_v[i].head);
			// 递归
			find_layer_closedContours(head, tail_next, vec_v_next, cc_buffer_next);
		}
		// 判断轮廓线段能否连入曲线
		else if (isCoincident(tail, vec_v[i].tail))
		{
			VertexType tail_next;
			vector<VectorType> vec_v_next;
			PointSet cc_buffer_next;
			tail_next = vec_v[i].head;
			vec_v_next = vec_v;
			// 从轮廓线段集中移除已连入曲线的线段
			vec_v_next.erase(vec_v_next.begin() + i);
			cc_buffer_next = cc_buffer;
			cc_buffer_next.points.push_back(vec_v[i].tail);
			// 递归
			find_layer_closedContours(head, tail_next, vec_v_next, cc_buffer_next);
		}
	}
	return;
}

void Stl2pointCould::to3DMatrix(void)
{
	LayerType *pl;
	pl = HeadLayer;
	int xnum_total = int((xmax - xmin) / mPrecisionX) + 1;
	int ynum_total = int((ymax - ymin) / mPrecisionY) + 1;
	xx.clear();
	yy.clear();
	zz.clear();
	double xt, yt, zi, xi, yi, zf;
	VertexType p_uu, p_u, p_v, p_w, p_ww, p_buffer;
	vector<long> index_layer;
	long ind;
	PointSet cc_buffer;
	vector<PointSet> ccs_buffer;

	// 创建进度提示框
	QProgressDialog progressDialog("to3DMatrix", "取消", 0, slicenumber_total);
	progressDialog.setWindowTitle(QString("to3DMatrix"));
	progressDialog.setLabelText(QString("to3DMatrix.."));
	progressDialog.setValue(0);
	progressDialog.setWindowModality(Qt::WindowModal);
	progressDialog.setAutoClose(false);
	progressDialog.setAutoReset(false);
	progressDialog.show();
	QApplication::processEvents();
	// 创建事件循环
	QEventLoop eventLoop;
	QObject::connect(&progressDialog, &QProgressDialog::canceled, &eventLoop, &QEventLoop::quit);

	zi = zmin;
	for (long znum = 0; znum < slicenumber_total; znum++)
	{

		index_layer.clear();
		vector<double> iPointsY;
		xi = xmin;

			for (long xnum = 0; xnum < xnum_total; xnum++)
			{
				iPointsY.clear();
				for (long ccnum = 0; ccnum < Solid[znum].closedContours.size(); ccnum++)
				{
					vector<VertexType> cc;
					cc = Solid[znum].closedContours[ccnum].points;
					for (long pnum = 0; pnum < cc.size(); pnum++)
					{
						// 读取此点，前点和后点
						p_v = cc[pnum];
						p_u = cc[(pnum - 1) % cc.size()];
						p_uu = cc[(pnum - 2) % cc.size()];
						p_w = cc[(pnum + 1) % cc.size()];
						p_ww = cc[(pnum + 2) % cc.size()];
						// p_now在xi上
						if (fabs(p_v.x - xi) < allowError)
						{
							if ((fabs(p_u.x - xi) > allowError) && (fabs(p_w.x - xi) > allowError) && (((p_u.x - xi) * (p_w.x - xi)) < 0))
								iPointsY.push_back(p_v.y);
							else if ((fabs(p_u.x - xi) < allowError) && (((p_uu.x - xi) * (p_w.x - xi)) < 0))
								iPointsY.push_back((p_v.y + p_u.y) / 2);
							else if ((fabs(p_w.x - xi) < allowError) && (((p_u.x - xi) * (p_ww.x - xi)) < 0))
								iPointsY.push_back((p_v.y + p_w.y) / 2);
						}

						// p_now不在xi上
						else if ((fabs(p_w.x - xi) > allowError))
						{
							// p_now在xi右，p_next在xi左
							if ((p_v.x > xi + allowError) && (p_w.x < xi - allowError))
							{
								yt = p_v.y - (p_v.y - p_w.y) / (p_v.x - p_w.x) * (p_v.x - xi);
								iPointsY.push_back(yt);
							}
							// p_now在xi左，p_next在xi右
							if ((p_v.x < xi - allowError) && (p_w.x > xi + allowError))
							{
								yt = p_v.y - (p_v.y - p_w.y) / (p_v.x - p_w.x) * (p_v.x - xi);
								iPointsY.push_back(yt);
							}
						}
					}
				}
				sort(iPointsY.begin(), iPointsY.end());
				iPointsY.erase(unique(iPointsY.begin(), iPointsY.end()), iPointsY.end());
				yi = ymin;
				if (iPointsY.size() != 0)
				{
					for (long ynum = 0; ynum < ynum_total; ynum++)
					{
						if (xi >= -29.4 && xi <= -29.0 && yi <= -7.6 && yi >= -8.0)
						{
							int a = iPointsY.size();
						}
						if (Solid[znum].Hatch.size() != 0)
						{
							for (int hnum = 0; hnum < Solid[znum].Hatch.size(); hnum++)
							{
								// 在三角片内
								if (interpolateZCoordinate(xi, yi, Solid[znum].Hatch[hnum]) != DBL_MIN)
								{
									ind = znum * xnum_total * ynum_total + ynum * xnum_total + xnum;
									vector<long>::iterator it = find(index_layer.begin(), index_layer.end(), ind);
									if (it == index_layer.end())
									{
										index_layer.push_back(ind);
										index.push_back(ind);
										Solid[znum].pointCloud.push_back(toVertexType(xi, yi, zi));
									}
									break;
								}

							}
						}
						for (int ii = 0; ii < iPointsY.size() - 1; ii++)
						{
							if (yi == iPointsY[ii])
							{
								ind = znum * xnum_total * ynum_total + ynum * xnum_total + xnum;
								vector<long>::iterator it = find(index_layer.begin(), index_layer.end(), ind);
								if (it == index_layer.end())
								{
									index_layer.push_back(ind);
									index.push_back(ind);
									Solid[znum].pointCloud.push_back(toVertexType(xi, yi, zi));
								}
								break;
							}
							if (yi > iPointsY[ii] && yi < iPointsY[ii + 1])
							{
								if (ii % 2 == 0 && Solid[znum].Hatch.size() == 0)
								{
									ind = znum * xnum_total * ynum_total + ynum * xnum_total + xnum;
									vector<long>::iterator it = find(index_layer.begin(), index_layer.end(), ind);
									if (it == index_layer.end())
									{
										index_layer.push_back(ind);
										index.push_back(ind);
										Solid[znum].pointCloud.push_back(toVertexType(xi, yi, zi));
									}
									break;
								}
								else if (ii>0 && ii<iPointsY.size()-1 && Solid[znum].Hatch.size() != 0)
								{
									int zu = 0;
									int zd = 0;
									vector<double> Zf;
									for (long fnum = 0; fnum < FacetArray.size(); fnum++)
									{
										if (xi < min(min(FacetArray[fnum].P1.x, FacetArray[fnum].P2.x), FacetArray[fnum].P3.x)
											|| xi > max(max(FacetArray[fnum].P1.x, FacetArray[fnum].P2.x), FacetArray[fnum].P3.x)
											|| yi < min(min(FacetArray[fnum].P1.y, FacetArray[fnum].P2.y), FacetArray[fnum].P3.y)
											|| yi> max(max(FacetArray[fnum].P1.y, FacetArray[fnum].P2.y), FacetArray[fnum].P3.y)) {
											continue;
										}
										zf = interpolateZCoordinate(xi, yi, FacetArray[fnum]);
										if (!binary_search(Zf.begin(), Zf.end(), zf))
										{
											Zf.push_back(zf);
											if (zf > zi)
												zu++;
											else if (zf > zmin + allowError)
												zd++;
										}

									}
									// 在实体内部
									if (zu % 2 == 1 && zd % 2 == 1)
									{
										ind = znum * xnum_total * ynum_total + ynum * xnum_total + xnum;
										vector<long>::iterator it = find(index_layer.begin(), index_layer.end(), ind);
										if (it == index_layer.end())
										{
											index_layer.push_back(ind);
											index.push_back(ind);
											Solid[znum].pointCloud.push_back(toVertexType(xi, yi, zi));

										}
										break;
									}
								}
								
							}
						}
						yi += mPrecisionY;
					}

				}
				xi += mPrecisionX;
			}
			iPointsY.clear();
		zi += mPrecisionZ;
		progressDialog.setValue(znum + 1);
		QApplication::processEvents();
		// 检查是否点击了"取消"按钮
		if (progressDialog.wasCanceled())
		{
			break; // 退出循环
		}
	}
	// 关闭进度提示框
	QApplication::processEvents();
	progressDialog.close();
}

VertexType Stl2pointCould::toVertexType(float x, float y, float z)
{
	VertexType p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}




double Stl2pointCould::interpolateZCoordinate(float x0, float y0, FacetType facet)
{
	double d = (facet.P2.y - facet.P3.y) * (facet.P1.x - facet.P3.x) - (facet.P2.x - facet.P3.x) * (facet.P1.y - facet.P3.y);
	double alpha = ((facet.P2.y - facet.P3.y) * (x0 - facet.P3.x) - (facet.P2.x - facet.P3.x) * (y0 - facet.P3.y)) / d;
	double beta = ((facet.P3.y - facet.P1.y) * (x0 - facet.P3.x) - (facet.P3.x - facet.P1.x) * (y0 - facet.P3.y)) / d;
	double gamma = 1 - alpha - beta;

	if (alpha >= 0 && beta >= 0 && gamma >= 0)
		return alpha * facet.P1.z + beta * facet.P2.z + gamma * facet.P3.z;
	else
		return DBL_MIN;
}

bool Stl2pointCould::areCollinear(const VertexType& p1, const VertexType& p2, const VertexType& p3) {
	return abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y)) <= allowError * allowError;
}

void Stl2pointCould::removeIntermediatePoints(PointSet& closedContour) {
	vector<VertexType> result;
	result.push_back(closedContour.points[0]);  

	for (int i = 1; i < closedContour.points.size()-1; ++i) {
		if (!areCollinear(result.back(), closedContour.points[i], closedContour.points[i + 1])) {
			result.push_back(closedContour.points[i]);
		}
	}
	result.push_back(closedContour.points.back());  
	rotate(result.begin(), result.begin() + 2, result.end());
	for (int i = 0; i < 2 && result.size()>3; i++)
	{
		if (areCollinear(result[result.size() - 1], result[result.size() - 2], result[result.size() - 3]))
		{
			bool b = areCollinear(result[result.size() - 1], result[result.size() - 2], result[result.size() - 3]);
			result[result.size() - 2] = result[result.size() - 1];
			result.pop_back();
		}
	}
	closedContour.points = result;  
}

// 检查两条曲线是否共点的函数
bool Stl2pointCould::doContoursShareCommonPoint(PointSet Contour1, PointSet Contour2)
{
	for (const VertexType& vertex1 : Contour1.points) {
		for (const VertexType& vertex2 : Contour2.points) {
			if (vertex1.x == vertex2.x && vertex1.y == vertex2.y && vertex1.z == vertex2.z) {
				return true;  // Common point found
			}
		}
	}
	return false;  // No common point found
}

// 检查点是否在封闭曲线内的函数
bool Stl2pointCould::isPointInsideClosedContour(PointSet Contour, const VertexType& point)
{
	int crossings = 0;
	int numVertices = Contour.points.size();
	for (int i = 0; i < numVertices; ++i) {
		const VertexType& vertex1 = Contour.points[i];
		const VertexType& vertex2 = Contour.points[(i + 1) % numVertices];

		// Check if the point is on the same horizontal line as the edge
		if ((vertex1.y <= point.y && vertex2.y > point.y) || (vertex1.y > point.y && vertex2.y <= point.y)) {
			// Check if the point is to the left of the edge
			double edgeX = vertex1.x + (point.y - vertex1.y) / (vertex2.y - vertex1.y) * (vertex2.x - vertex1.x);
			if (point.x < edgeX) {
				crossings++;
			}
		}
	}
	return (crossings % 2 != 0);
}

// 检查曲线是否在封闭曲线内的函数
bool Stl2pointCould::isContourContained(const PointSet& outerContour, const PointSet& innerContour) 
{
	for (const VertexType& vertex : innerContour.points) {
		if (!isPointInsideClosedContour(outerContour, vertex)) {
			return false;
		}
	}
	return true;
}

vector<PointSet> Stl2pointCould::removeInnerContours(vector<PointSet> ccs_buffer)
{
	vector<PointSet> ccs;
	ccs = ccs_buffer;
	vector<int> curvesToRemove;
	for (int i = 0; i < ccs.size(); ++i)
	{
		for (int j = 0; j < ccs.size(); ++j)
		{
			if (i != j)
			{
				if (isContourContained(ccs[i], ccs[j]) && doContoursShareCommonPoint(ccs[i], ccs[j]))
				{
					curvesToRemove.push_back(j);
				}
			}
		}
	}
	for (int rnum : curvesToRemove) {
		ccs.erase(ccs.begin() + rnum);
	}
	return ccs;
}


