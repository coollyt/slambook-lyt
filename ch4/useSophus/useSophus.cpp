#include <iostream> 
#include <cmath> 
using namespace std; 

#include <Eigen/Core> 
#include <Eigen/Geometry> 

#include "sophus/so3.h" 
#include "sophus/se3.h" 

int main( int argc, char** argv )
{ 
   // 沿 Z 轴转 90 度的旋转矩阵 
   Eigen::Matrix3d R =Eigen::AngleAxisd(M_PI/2, Eigen::Vector3d(0,0,1)).toRotationMatrix();
   Sophus::SO3 SO3_R(R); 
   // Sophus::SO(3) 可以直接从旋转矩阵构造 
   Sophus::SO3 SO3_v( 0, 0, M_PI/2 ); 
   // 亦可从旋转向量构造 
   Eigen::Quaterniond q(R); 
   // 或者四元数 
   Sophus::SO3 SO3_q(q); 
   // 上述表达方式都是等价的 
   // 输出 SO(3) 时， 以 so(3) 形式输出 
   cout<<"SO(3) from matrix: " <<SO3_R<<endl; 
   cout<<"SO(3) from vector: " <<SO3_v<<endl;
   cout<<"SO(3) from quaternion : "<<SO3_q<<endl;
   
   
   // 使用对数映射获得它的李代数 
   Eigen::Vector3d so3 = SO3_R.log(); 
   cout<<"so3 = " <<so3.transpose()<<endl; 
   // hat 为向量到反对称矩阵 
   cout<<"so3 hat="<<Sophus::SO3::hat(so3)<<endl; 
   // 相对的， vee 为反对称到向量 
   cout<<"so3 hat vee="<<Sophus::SO3::vee( Sophus::SO3::hat(so3) ).transpose()<<endl; 
   
   
   // 增量扰动模型的更新 
   Eigen::Vector3d update_so3(1e-4, 0, 0); 
   // 假设更新量有这么多 
   Sophus::SO3 SO3_updated = Sophus::SO3::exp(update_so3)*SO3_R; 
   // 左乘更新 
   cout<<"SO3 updated = " <<SO3_updated<<endl; 
   
  
   cout<<"************ 我是分割线 *************"<<endl; 
   // 对 SE(3) 操作大同小异 
   Eigen::Vector3d t(1,0,0); 
   // 沿 X 轴平移 1 
   Sophus::SE3 SE3_Rt(R, t); 
   // 从 R, t 构造 SE(3) 
   Sophus::SE3 SE3_qt(q,t);
   // 从 q, t 构造 SE(3) 
   cout<<"SE3 from R,t= " <<endl<<SE3_Rt<<endl; 
   cout<<"SE3 from q,t= " <<endl<<SE3_qt<<endl;
   // 李代数 se(3) 是一个六维向量， 方便起见先 typedef 一下 
   typedef Eigen::Matrix< double , 6,1> Vector6d; 
   Vector6d se3 = SE3_Rt.log(); 
   cout<<"se3 = " <<se3.transpose()<<endl; 
   // 观察输出， 会发现在 Sophus 中， se(3) 平移在前， 旋转在后。 与我们的书是一致的。 
   // 同样的， 有 hat 和 vee 两个算符 
   cout<<"se3 hat = "<<endl<<Sophus::SE3::hat(se3)<<endl; 
   cout<<"se3 hat vee = "<<Sophus::SE3::vee( Sophus::SE3::hat(se3) ).transpose()<<endl;
   
   
   // 最后， 演示一下更新 
    Vector6d update_se3; //更新量
    update_se3.setZero();
    update_se3(0, 0) = 1e-4d;
    Sophus::SE3 SE3_updated = Sophus::SE3::exp(update_se3)*SE3_Rt;
    cout << "SE3 updated = " << endl << SE3_updated.matrix()<<endl;

    return 0;
}
