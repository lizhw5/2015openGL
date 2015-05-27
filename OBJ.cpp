#define  _CRT_SECURE_NO_WARNINGS
#include"OBJ.h"
#include<iostream>
#include<fstream>
using namespace std;

/*****************辅助***************************/

enum FACE_STATE{V,V_TV,V_NV,V_TV_NV,NOT_YET_CLEAR};
struct Face_info
{
	FACE_STATE face_state;
	int v_num;
};
Face_info getFaceInfo(char* line,int result[]){
	long unsigned int sum = 0;
	int index = 0;
	FACE_STATE face_state = V;
	Face_info face_info;
	for(size_t i = 1;i<strlen(line) - 1;i++){
		if(line[i] == '/' && line[i+1] != '/'){
			result[index++] = sum;
			sum = 0;
			face_state = NOT_YET_CLEAR;
		}else if(line[i] == '/' && line[i+1] == '/'){
			i++;
			result[index++] = sum;
			sum = 0;
			face_state = V_NV;
		}else if(line[i] == ' '){
			result[index++] = sum;
			sum = 0;
		}else{
			sum = sum*10 + line[i] - '0';
		}
	}

	result[index++] = sum;//存入最后一个数字
	if(face_state == NOT_YET_CLEAR && index%2 == 0){
		face_state = V_TV;
	}
	if(face_state == NOT_YET_CLEAR && index%2 == 1){
		face_state = V_TV_NV;
	}
	face_info.face_state = face_state;
	face_info.v_num = index;
	return face_info;
}


/**************辅助结束*********************/


void cPoint::render(const cOBJ &Obj){


	glBegin(GL_POINTS);               //开始画点

	glVertex3dv((double*)&(Obj.Vertexs[this->VIndex]));

	glEnd();                          //结束画点
}

void cLine::render(const cOBJ &Obj){}	//waiting...

cFace::cFace(){}
void cFace::render(cOBJ &Obj){
	for(size_t i = 0;i<Obj.Faces.size();i++){
		//注意加上判断是否有材质
		if(Obj.Faces[i].Mindex != -1){
			(Obj.Materials[Obj.Faces[i].Mindex]).setMaterial();
		}
		glBegin(GL_POLYGON);
		for(size_t j = 0;j<Obj.Faces[i].Vindexs.size();j++){

			//切记索引要-1
			if(Obj.Faces[i].Vindexs[j].m_bVt){
				if(Obj.TVertex[Obj.Faces[i].Vindexs[j].m_nVtI-1].fT == -1){
					glTexCoord2f(Obj.TVertex[Obj.Faces[i].Vindexs[j].m_nVtI-1].fP,
						Obj.TVertex[Obj.Faces[i].Vindexs[j].m_nVtI-1].fS);
				}
				else{
					glTexCoord3f(Obj.TVertex[Obj.Faces[i].Vindexs[j].m_nVtI-1].fP,
						Obj.TVertex[Obj.Faces[i].Vindexs[j].m_nVtI-1].fS,
						Obj.TVertex[Obj.Faces[i].Vindexs[j].m_nVtI-1].fT);
				}
			}
			glVertex3f(Obj.Vertexs[Obj.Faces[i].Vindexs[j].m_nVI-1].fX,
				Obj.Vertexs[Obj.Faces[i].Vindexs[j].m_nVI-1].fY,
				Obj.Vertexs[Obj.Faces[i].Vindexs[j].m_nVI-1].fZ);
		}

		glEnd();
	}

}

cOBJ::cOBJ(){}
cOBJ::cOBJ(const char* FilePath){
		FILE *OBJ = fopen(FilePath,"r");
	if(OBJ == NULL){
		cout<<"ERROR : Please check out whether the file "<<FilePath<<" "<<"is exist..."<<endl;
		return ;
	}
	char ALine[128];
	int index = 0,materials_index = -1;
	while(fscanf(OBJ,"%s",ALine) != EOF){
		if (strcmp( ALine, "v" ) == 0){  
			sVertex s_vertex;
			cPoint c_point;
			c_point.VIndex = index++;
			fscanf(OBJ, "%lf %lf %lf\n", &(s_vertex.fX), &(s_vertex.fY), &(s_vertex.fZ));
			this->Vertexs.push_back(s_vertex);
			this->Points.push_back(c_point);

		}else if(strcmp( ALine, "f" ) == 0){//支持最多10个顶点的面
			char contents[128];
			int face_vertex[30];
			cFace c_face;
			sVertexData s_vertex_data;
			fgets(contents,127,OBJ);//注意这里contents的首个字符为空格键,getFaceInfo函数会处理
			Face_info face_info = getFaceInfo(contents,face_vertex);

			c_face.Mindex = materials_index;
			switch (face_info.face_state)
			{
			case(V):
				for(int i = 0;i<face_info.v_num;i++){				
					s_vertex_data.m_bVn = false;
					s_vertex_data.m_bVt = false;
					s_vertex_data.m_nVI = face_vertex[i];
					s_vertex_data.m_nVnI = -1;
					s_vertex_data.m_nVtI = -1;
					c_face.Vindexs.push_back(s_vertex_data);
				}
				this->Faces.push_back(c_face);
				break;
			case(V_TV):
				for(int i = 0;i<face_info.v_num;i+=2){
					s_vertex_data.m_bVn = false;
					s_vertex_data.m_bVt = true;
					s_vertex_data.m_nVI = face_vertex[i];
					s_vertex_data.m_nVnI = -1;
					s_vertex_data.m_nVtI = face_vertex[i+1];
					c_face.Vindexs.push_back(s_vertex_data);
				}
				this->Faces.push_back(c_face);
				break;
			case(V_NV):
				for(int i = 0;i<face_info.v_num;i+=2){
					s_vertex_data.m_bVn = true;
					s_vertex_data.m_bVt = false;
					s_vertex_data.m_nVI = face_vertex[i];
					s_vertex_data.m_nVnI = face_vertex[i+1];
					s_vertex_data.m_nVtI = -1;
					c_face.Vindexs.push_back(s_vertex_data);
				}
				this->Faces.push_back(c_face);
				break;
			case(V_TV_NV):
				for(int i = 0;i<face_info.v_num;i+=3){
					s_vertex_data.m_bVn = true;
					s_vertex_data.m_bVt = true;
					s_vertex_data.m_nVI = face_vertex[i];
					s_vertex_data.m_nVnI = face_vertex[i+1];
					s_vertex_data.m_nVtI = face_vertex[i+2];
					c_face.Vindexs.push_back(s_vertex_data);
				}
				this->Faces.push_back(c_face);
				break;
			}


		}else if(strcmp( ALine, "vn" ) == 0){
			sNormalVertex s_normal_vertex;
			fscanf(OBJ, "%lf %lf %lf\n", &(s_normal_vertex.fX), &(s_normal_vertex.fY), &(s_normal_vertex.fZ));
			this->NVertex.push_back(s_normal_vertex);
		}else if(strcmp( ALine, "vt" ) == 0){
			sTextureVertex s_texture_vertex;
			int par_num  = fscanf(OBJ, "%lf %lf %lf\n", &(s_texture_vertex.fP), &(s_texture_vertex.fS), &(s_texture_vertex.fT));
			if(par_num == 2){
				s_texture_vertex.fT = -1;
			}

			this->TVertex.push_back(s_texture_vertex);
		}else if(strcmp( ALine, "mtllib" ) == 0){
			char path[PATH_SIZE];
			fscanf(OBJ, "%s\n", path);
			loadMaterialFromFile(path);
		}else if(strcmp( ALine, "usemtl" ) == 0){
			//使用材质
			char material_name[PATH_SIZE];
			fscanf(OBJ, "%s\n", material_name);
			for(size_t i = 0;i<this->Materials.size();i++){
				if(strcmp(this->Materials[i].MaterialName,material_name) == 0){
					materials_index = i;
					break;
				}
			}

		}
	}

}
bool cOBJ::loadObjFromFile(const char* FilePath){

	FILE *OBJ = fopen(FilePath,"r");
	if(OBJ == NULL){
		cout<<"ERROR : Please check out whether the file "<<FilePath<<" "<<"is exist..."<<endl;
		return false;
	}
	char ALine[128];
	int index = 0,materials_index = -1;
	while(fscanf(OBJ,"%s",ALine) != EOF){
		if (strcmp( ALine, "v" ) == 0){  
			sVertex s_vertex;
			cPoint c_point;
			c_point.VIndex = index++;
			fscanf(OBJ, "%lf %lf %lf\n", &(s_vertex.fX), &(s_vertex.fY), &(s_vertex.fZ));
			this->Vertexs.push_back(s_vertex);
			this->Points.push_back(c_point);

		}else if(strcmp( ALine, "f" ) == 0){//支持最多10个顶点的面
			char contents[128];
			int face_vertex[30];
			cFace c_face;
			sVertexData s_vertex_data;
			fgets(contents,127,OBJ);//注意这里contents的首个字符为空格键,getFaceInfo函数会处理
			Face_info face_info = getFaceInfo(contents,face_vertex);

			c_face.Mindex = materials_index;
			switch (face_info.face_state)
			{
			case(V):
				for(int i = 0;i<face_info.v_num;i++){				
					s_vertex_data.m_bVn = false;
					s_vertex_data.m_bVt = false;
					s_vertex_data.m_nVI = face_vertex[i];
					s_vertex_data.m_nVnI = -1;
					s_vertex_data.m_nVtI = -1;
					c_face.Vindexs.push_back(s_vertex_data);
				}
				this->Faces.push_back(c_face);
				break;
			case(V_TV):
				for(int i = 0;i<face_info.v_num;i+=2){
					s_vertex_data.m_bVn = false;
					s_vertex_data.m_bVt = true;
					s_vertex_data.m_nVI = face_vertex[i];
					s_vertex_data.m_nVnI = -1;
					s_vertex_data.m_nVtI = face_vertex[i+1];
					c_face.Vindexs.push_back(s_vertex_data);
				}
				this->Faces.push_back(c_face);
				break;
			case(V_NV):
				for(int i = 0;i<face_info.v_num;i+=2){
					s_vertex_data.m_bVn = true;
					s_vertex_data.m_bVt = false;
					s_vertex_data.m_nVI = face_vertex[i];
					s_vertex_data.m_nVnI = face_vertex[i+1];
					s_vertex_data.m_nVtI = -1;
					c_face.Vindexs.push_back(s_vertex_data);
				}
				this->Faces.push_back(c_face);
				break;
			case(V_TV_NV):
				for(int i = 0;i<face_info.v_num;i+=3){
					s_vertex_data.m_bVn = true;
					s_vertex_data.m_bVt = true;
					s_vertex_data.m_nVI = face_vertex[i];
					s_vertex_data.m_nVnI = face_vertex[i+1];
					s_vertex_data.m_nVtI = face_vertex[i+2];
					c_face.Vindexs.push_back(s_vertex_data);
				}
				this->Faces.push_back(c_face);
				break;
			}


		}else if(strcmp( ALine, "vn" ) == 0){
			sNormalVertex s_normal_vertex;
			fscanf(OBJ, "%lf %lf %lf\n", &(s_normal_vertex.fX), &(s_normal_vertex.fY), &(s_normal_vertex.fZ));
			this->NVertex.push_back(s_normal_vertex);

		}else if(strcmp( ALine, "vt" ) == 0){
			sTextureVertex s_texture_vertex;
			int par_num  = fscanf(OBJ, "%lf %lf %lf\n", &(s_texture_vertex.fP), &(s_texture_vertex.fS), &(s_texture_vertex.fT));
			if(par_num == 2){
				s_texture_vertex.fT = -1;
			}
			this->TVertex.push_back(s_texture_vertex);

		}else if(strcmp( ALine, "mtllib" ) == 0){
			char path[PATH_SIZE];
			fscanf(OBJ, "%s\n", path);
			loadMaterialFromFile(path);
		}else if(strcmp( ALine, "usemtl" ) == 0){
			//使用材质
			char material_name[PATH_SIZE];
			fscanf(OBJ, "%s\n", material_name);
			for(size_t i = 0;i<this->Materials.size();i++){
				if(strcmp(this->Materials[i].MaterialName,material_name) == 0){
					materials_index = i;
					break;
				}
			}

		}
	}

	return true;
}

bool cOBJ::loadMaterialFromFile(const char* FilePath){

	FILE *OBJ = fopen(FilePath,"r");
	if(OBJ == NULL){
		cout<<"ERROR : Please check out whether the file "<<FilePath<<" "<<"is exist..."<<endl;
		return false;
	}
	char ALine[128];
	int index = -1;
	while(fscanf(OBJ,"%s",ALine) != EOF){
		if (strcmp( ALine, "newmtl" ) == 0){  
			cMaterial c_material;
			this->Materials.push_back(c_material);
			index++;
			fscanf(OBJ,"%s",this->Materials[index].MaterialName);
		}
		int para_num = -1;
		if(strcmp(ALine,"Ka") == 0){
			para_num = fscanf(OBJ,"%f %f %f %f",&(this->Materials[index].ambient[0]),&(this->Materials[index].ambient[1]),
				&(this->Materials[index].ambient[2]),&(this->Materials[index].ambient[3]));
			if(para_num == 3){
				this->Materials[index].ambient[3] = -1;
			}
		}
		else if(strcmp(ALine,"Kd") == 0){
			para_num = fscanf(OBJ,"%f %f %f %f",&(this->Materials[index].diffuse[0]),&(this->Materials[index].diffuse[1]),
				&(this->Materials[index].diffuse[2]),&(this->Materials[index].diffuse[3]));
			if(para_num == 3){
				this->Materials[index].diffuse[3] = -1;
			}
		}
		else if(strcmp(ALine,"Ks") == 0){
			para_num = fscanf(OBJ,"%f %f %f %f",&(this->Materials[index].specular[0]),&(this->Materials[index].specular[1]),
				&(this->Materials[index].specular[2]),&(this->Materials[index].specular[3]));
			if(para_num == 3){
				this->Materials[index].specular[3] = -1;
			}
		}
		else if(strcmp(ALine,"Ke") == 0){
			para_num = fscanf(OBJ,"%f %f %f %f",&(this->Materials[index].emission[0]),&(this->Materials[index].emission[1]),
				&(this->Materials[index].emission[2]),&(this->Materials[index].emission[3]));
			if(para_num == 3){
				this->Materials[index].emission[3] = -1;
			}
		}
		else if(strcmp(ALine,"map_Kd") == 0){
			fscanf(OBJ,"%s",this->Materials[index].texturePath);
			this->Materials[index].initTexture();
		}
	}

	return true;
}

void cOBJ::render(){
	for(size_t i = 0;i<this->Faces.size();i++){
		this->Faces[i].render(*this);
	}
}




//测试使用
void cOBJ::print_vetor(){

	/*
	//顶点信息
	for(size_t i = 0;i<this->Vertexs.size();i++){
		cout<<"x : "<<this->Vertexs[i].fX<<"y : "<<this->Vertexs[i].fY<<"z : "<<this->Vertexs[i].fZ<<endl;
	}
	*/
	//obj信息
	for(size_t i = 0;i<this->Faces.size();i++){
		for(size_t j = 0;j<this->Faces[i].Vindexs.size();j++){
			//cout<<"F_V : "<<this->Faces[i].Vindexs[j].m_nVI<<endl;
			//cout<<"F_VN : "<<this->Faces[i].Vindexs[j].m_bVn<<"  "<<this->Faces[i].Vindexs[j].m_nVnI<<endl;
			cout<<"F_VT : "<<this->Faces[i].Vindexs[j].m_bVt<<"  "<<this->Faces[i].Vindexs[j].m_nVtI<<"values: "<<this->TVertex[this->Faces[i].Vindexs[j].m_nVtI-1].fP<<endl;
			//cout<<"index : "<<this->Faces[i].Mindex<<endl;
		}
	}

	/*
	//mtl信息
	for(size_t i = 0;i<this->Materials.size();i++){
		for(size_t j = 0;j<this->Materials[i].ambient.size();j++){
			cout<<"ambient : "<<this->Materials[i].ambient[j]<<endl;
		}
		for(size_t j = 0;j<this->Materials[i].diffuse.size();j++){
			cout<<"diffuse : "<<this->Materials[i].diffuse[j]<<endl;
		}
		for(size_t j = 0;j<this->Materials[i].specular.size();j++){
			cout<<"specular : "<<this->Materials[i].specular[j]<<endl;
		}
		for(size_t j = 0;j<this->Materials[i].emission.size();j++){
			cout<<"emission : "<<this->Materials[i].emission[j]<<endl;
		}
	}
	*/
}
