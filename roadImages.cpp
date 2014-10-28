#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc,char *argv[]){
/*
	if(!argv[1]){
		printf("you need to input an image.\n");
		return -1;
	}
	*/

	int i;
	char fileName[256];
	cv::Mat diffImg,gryImg,dstImg;
	cv::Mat bg = cv::imread("bg.bmp",1);


	for(i=0;i<200;i++){
		sprintf(fileName,"../data/%d.bmp",17800 + i);
		cv::Mat inputImg = cv::imread(fileName,1);

		//背景差分
		cv::absdiff(inputImg,bg,diffImg);
		//濃淡画像に
		cv::cvtColor(diffImg,gryImg,CV_BGR2GRAY);
		//閾値でニ値化
		cv::threshold(gryImg,dstImg,20,255,cv::THRESH_BINARY || cv::THRESH_OTSU);

		//収縮と膨張
//		dilate(dstImg,dstImg,cv::Mat(),cv::Point(-1,-1),1);
//		dilate(dstImg,dstImg,cv::Mat(),cv::Point(-1,-1),1);
//		erode(dstImg,dstImg,cv::Mat(),cv::Point(-1,-1),1);
//		erode(dstImg,dstImg,cv::Mat(),cv::Point(-1,-1),1);
//		RGBでの単純な差(絶対)と内積を使って(かつ)、膨張と収縮できれいな形にした

		std::vector<std::vector<cv::Point> > contours;
		
		// 輪郭の検出
		cv::findContours(dstImg, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);

		for(int k = 0; k < contours.size(); ++k) {
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
			int j;
			if((box.size.width / box.size.height) > 0.85 && (box.size.width / box.size.height) < 1.15){
				for(j=0;j<4;j++){
					//	printf("round (%f,%f),(%f, %f)\n",vertices[j].x,vertices[j].y,vertices[j+1].x,vertices[j+1].y);
					cv::line(inputImg,vertices[j],vertices[(j+1)%4],cv::Scalar(0,255,0));
				}
				printf("%d: %f %f\n",17800+i,box.size.width,box.size.height);
			}
			// 楕円の描画
			//cv::ellipse(inputImg, box, cv::Scalar(0,0,255), 2, CV_AA);
			//cv::ellipse(inputImg, box, cv::Scalar(0,0,255), 2, CV_AA);
		}

		//書き出し
		char name[256];
		sprintf(name,"outputs/dst/dst_%d.bmp",17800+i);
		cv::imwrite(name,dstImg);

		sprintf(name,"outputs/roundFit/roundFit_%d.bmp",17800+i);
		cv::imwrite(name,inputImg);

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

	return 0;
}
