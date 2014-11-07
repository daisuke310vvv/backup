#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

bool roundFitting(cv::Mat *m);

void houghCircle(cv::Mat *im,cv::Mat m);

int main(int argc,char *argv[]){
/*
	if(!argv[1]){
		printf("you need to input an image.\n");
		return -1;
	}
	*/

	/* ------------------------------------------------------------------------ */
	// declare variables
	/* ------------------------------------------------------------------------ */
	int i,k,j,ballFoundCount=0;
	char fileName[256];
	cv::Mat diffImg,gryImg,dstImg;
	cv::Mat bg = cv::imread("bg.bmp",1);
	std::vector<std::vector<cv::Point> > contours;
	/* ------------------------------------------------------------------------ */

	int isFound = 0;
	int count = 1;

	for(i=0;i<57;i++){

		isFound = 0;

		/* -------------------------------------------------------------------- */
		// input
		/* -------------------------------------------------------------------- */
		sprintf(fileName,"../data/%d.bmp",17800 + i);
		cv::Mat inputImg = cv::imread(fileName,1);
		/* -------------------------------------------------------------------- */


		/* -------------------------------------------------------------------- */
		// 前処理(-> 背景差分 -> 濃淡画像 -> ニ値化)
		/* -------------------------------------------------------------------- */
		cv::absdiff(inputImg,bg,diffImg);
		cv::cvtColor(diffImg,gryImg,CV_BGR2GRAY);
		//平滑化
		cv::GaussianBlur(gryImg,gryImg,cv::Size(9,9),2,2);
		//cv::threshold(gryImg,dstImg,20,255,cv::THRESH_BINARY || cv::THRESH_OTSU);
		//Canny
		//cv::Canny(gryImg,dstImg,10,100,3);
		/* -------------------------------------------------------------------- */


		//収縮と膨張
		//cv::dilate(dstImg,dstImg,cv::Mat(),cv::Point(-1,-1),1);
		//cv::dilate(dstImg,dstImg,cv::Mat(),cv::Point(-1,-1),1);
		//cv::erode(dstImg,dstImg,cv::Mat(),cv::Point(-1,-1),1);
		//cv::erode(dstImg,dstImg,cv::Mat(),cv::Point(-1,-1),1);

//		RGBでの単純な差(絶対)と内積を使って(かつ)、膨張と収縮できれいな形にした

		
		/* -------------------------------------------------------------------- */
		// 楕円フィッティング処理
		// 入力(dstImg)
		/* -------------------------------------------------------------------- */
		// 輪郭の検出
		//cv::findContours(dstImg, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		//TODO: 輪郭の点の間を出力

		//書き出し
		//char name[256];
		//sprintf(name,"outputs/dst/dst_%d.bmp",17800+i);
		//cv::imwrite(name,dstImg);

		/* -------------------------------------------------------------------- */
		// contours : 検出された輪郭の数分配列に格納されている
		/* -------------------------------------------------------------------- */
		houghCircle(&inputImg,gryImg);

/*
		for(k = 0; k < contours.size(); ++k) {


			size_t count = contours[k].size();

			if(count < 50 || count > 1000) continue; // （小さすぎる|大きすぎる）輪郭を除外

			cv::Mat pointsf;
			cv::Mat(contours[k]).convertTo(pointsf, CV_32F);

			// 楕円フィッティング
			cv::RotatedRect box = fitEllipse(pointsf);
		//	printf("%f,%f\n",box.size.width,box.size.height);
			cv::Rect rect = box.boundingRect();
			cv::Point2f vertices[4];
			box.points(vertices);

			if((box.size.width / box.size.height) > 0.875 && (box.size.width / box.size.height) < 1.125){

				for(j=0;j<4;j++){
					//	printf("round (%f,%f),(%f, %f)\n",vertices[j].x,vertices[j].y,vertices[j+1].x,vertices[j+1].y);
					cv::line(inputImg,vertices[j],vertices[(j+1)%4],cv::Scalar(0,255,0));
				}
				printf("%d: %f %f\n",17800+i,box.size.width,box.size.height);
				if(isFound == 0){
					isFound++;
				}
			}

			// 楕円の描画
			cv::ellipse(inputImg, box, cv::Scalar(0,0,255), 1, CV_AA);
			//cv::ellipse(inputImg, box, cv::Scalar(0,0,255), 2, CV_AA);
		}

		if(isFound != 0){
			ballFoundCount++;
		}
*/
		//書き出し
		char name[256];
		sprintf(name,"outputs/dst/dst_%d.bmp",17800+i);
		cv::imwrite(name,dstImg);

		//char name[256];
		sprintf(name,"outputs/roundFit/roundFit_%d.bmp",17800+i);
		//cv::imwrite(name,inputImg);

		printf("count %d\n",++count);

	}

	//背景差分
	/*
	for(i=0;i<200;i++){

		cv::Mat diffImg,gryImg,dstImg;
		cv::Mat inputImg = *images[i];
		cv::absdiff(inputImg,bg,diffImg);
		cv::cvtColor(diffImg,gryImg,CV_BGR2GRAY);
		cv::threshold(gryImg,dstImg,20,255,cv::THRESH_BINARY);
		char name[256];
		sprintf(name,"dst_%d.bmp",17800 + i);
		cv::imwrite(name,dstImg);

	}
	*/

	printf("Finished Loading Images!!\n");
	printf("%dフレーム中、%d回ボールを検知できました。\n",200,ballFoundCount);

	return 0;
}

void houghCircle(cv::Mat *im,cv::Mat m){

		std::vector<cv::Vec3f>circles;

		
		cv::HoughCircles(m,circles,CV_HOUGH_GRADIENT,2,50,10,100,10,50);

		/*
		 * ハフ変換の結果に対してボールの色情報検索
		 * */

		//printf("ciecles.size %lu\n",circles.size());


		for(size_t i = 0;i<circles.size();++i){
			cv::Point center(cvRound(circles[i][0]),cvRound(circles[i][1]));

			int radius = cvRound(circles[i][2]);

			//printf("cirlcle(%d %d) radius %d\n",center.x,center.y,radius);

			//円の中心を描画
			cv::circle(*im,center,3,cv::Scalar(0,255,0),-1,8,0);
			//円を描画
			cv::circle(*im,center,radius,cv::Scalar(0,0,255),3,8,0);

		}

}



bool roundFitting(cv::Mat *m){

	return 0;
}
