#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#if defined(_MSC_VER) && (_MSC_VER >= 1600)
# pragma execution_character_set("utf-8")
#endif

// 点类型
typedef struct VertexType
{
    float x, y, z;
} VertexType;
// 三角形面片类型
typedef struct FacetType
{
    float i, j, k; // 法向量的坐标
    VertexType P1; // 第一个顶点坐标
    VertexType P2; // 第二个顶点坐标
    VertexType P3; // 第三个顶点坐标
} FacetType;
// 向量类型
typedef struct VectorType
{
    VertexType head;
    VertexType tail;
} VectorType;

typedef struct PointSet
{
  vector<VertexType> points;
}PointSet;

// 层类型
typedef struct LayerType
{
    // 动态数组 向量类型结构体
    vector<VectorType> Contour;		//三角片与分层面的交线数组
    vector<PointSet> Hatch;
    vector<PointSet> closedContours;
    vector<VertexType> pointCloud;
    LayerType *pLayer;
} LayerType;


class Stl2pointCould
{
public:
    std::string stlstrpath; // 保存stl文件路径，注意一定要为CStringA，可以解决Unicode带来的问题
    std::string txtstrpath;
    std::string pcdstrpath;

    vector<FacetType> FacetArray;			   // 用以保存stl模型三角形平面的平面数组
    double xmin, xmax, ymin, ymax, zmin, zmax; // 用以存储stl文件所有顶点中各方向的极值
    double mPrecisionX;
    double mPrecisionY;
    double mPrecisionZ;						   // z方向切片层高
    long facetnumber;						   // stl三角形平面总数
    long slicenumber_total;					   // stl分层总数
    vector<double> xx, yy, zz;
    vector<long> index;
    long stl_line_totalnumber;									// 统计stl文件分层后的线段总数

    vector<PointSet> ccs_buffer;
    double GetMin(double x1, double x2, double x3, double min); // 获取四个参数中最小值
    double GetMax(double x1, double x2, double x3, double max); // 获取四个参数中最大值


    void Slice_ResortFacet(void); // 对stl三角形平面重新排序，这里是平移至非负，并使每个平面P1.z>=P2.z>=P3.z

    FacetType Orderfacet(FacetType facet); // 对三角形平面三个顶点排序
    void Slice_STL(void);				   // 分层stl文件

    double allowError; // stl文件分层允许误差

    LayerType *HeadLayer; // stl实体各层链表头指针

    vector< LayerType> Solid;

    VertexType IntersectLine(VertexType p1, VertexType p2, double zt); // 求P1，P2两点连线和zt分割面的交点

    double distPP(VertexType p1, VertexType p2);					   // 求P1，P2两点距离
    bool readStl(void);
    bool isRepeatLine(VectorType v,vector<VectorType> vec_v);
    bool isCoincident(VertexType p1,VertexType p2);
    bool isRepeatHead(VertexType head,vector<PointSet> cc_v);
    void find_closedContours(void);
    void find_layer_closedContours(VertexType head,VertexType tail,vector<VectorType> vec_v,PointSet cc_buffer);
    void to3DMatrix(void);

	bool isInsideTriangle(double x0, double y0, FacetType facet);
	double interpolateZCoordinate(double x0, double y0, FacetType facet);
};

