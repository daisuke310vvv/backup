#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

bool roundFitting(cv::Mat *m);

void houghCircle(cv::Mat *im,cv::Mat m);

int main(int argc,char *argv[]){

	/* ---------------------------------------------------------------------- */
	// declare variables
	/* ---------------------------------------------------------------------- */
	int i,k,j,ballFoundCount=0;
	char fileName[256];
	cv::Mat diffImg,gryImg,dstImg;
	cv::Mat bg = cv::imread("bg.bmp",1);
	std::vector<std::vector<cv::Point> > contours;
	/* ---------------------------------------------------------------------- */

		/* ------------------------------------------------------------------ */
		// input
		/* ------------------------------------------------------------------ */
		sprintf(fileName,"../data/%d.bmp",17800);
		cv::Mat inputImg = cv::imread(fileName,1);
		//cv::Mat inputImg = cv::imread("../roundFittingTest.jpg",1);
		/* ------------------------------------------------------------------ */

		/* ------------------------------------------------------------------ */
		// 前処理(-> 背景差分 -> 濃淡画像 -> ニ値化)
		/* ------------------------------------------------------------------ */
		//cv::absdiff(inputImg,bg,diffImg);
		cv::cvtColor(inputImg,gryImg,CV_BGR2GRAY);
		//平滑化
		cv::GaussianBlur(gryImg,gryImg,cv::Size(9,9),2,2);
		/* ------------------------------------------------------------------ */

		cv::imwrite("gaussian.bmp",gryImg);

		houghCircle(&inputImg,gryImg);

		char name[256];
		sprintf(name,"hough_circle_%d.bmp",17800);
		cv::imwrite(name,inputImg);

	return 0;
}

void houghCircle(cv::Mat *im,cv::Mat m){

		std::vector<cv::Vec3f>circles;

		cv::HoughCircles(m,circles,CV_HOUGH_GRADIENT,2,m.rows/4,10,100);

		printf("ciecles.size %lu\n",circles.size());


		for(size_t i = 0;i<circles.size();++i){
			cv::Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));

			int radius = cvRound(circles[i][2]);

			printf("cirlcle(%d %d) radius %d\n",center.x,center.y,radius);

			//円の中心を描画
			cv::circle(*im,center,3,cv::Scalar(0,255,0),-1,8,0);
			//円を描画
			cv::circle(*im,center,radius,cv::Scalar(0,0,255),3,8,0);

		}

}


