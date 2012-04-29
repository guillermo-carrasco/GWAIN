#include "Ranking.h"


struct Classified{
	std::string name;
	int			rank;
};

bool cond(Classified a, Classified b) {
    return a.rank > b.rank;
}

std::vector<Classified>	score;



CRanking::CRanking(){
}

CRanking::~CRanking(){
}


void CRanking::init() {

	score = std::vector<Classified>(MAX_RANK);

	input = CInput::pGetInstance();
	texman = CTextureManager::pGetInstance();
	escriptor = CWriter::getInstance();

	imatge_rank = texman->loadTexture("rank");

	std::fstream ranking;

    //Inicialització dels permisos: nomes lectura
    ranking.open("./data/ranking.txt", std::ios::in);
	//si no existeix
	if (ranking == 0) {
		ResetRanking();
		return;
	}

    int r;
    std::string n;

    //Inicialització del vector score (per a no treballar amb el fitxer)
    for (int i = 0; i < MAX_RANK; i++) {
        ranking >> n;
        score[i].name = n;
        ranking >> r;
        score[i].rank = r;
    }

    //Ordenem per puntuació
    sort(score.begin(), score.end(), cond);
    ranking.close();
}


bool CRanking::CheckScore(int s) {
    for (int i = 0; i < MAX_RANK; i++) if (s >= score[i].rank) return true;
    return false;
}


void CRanking::SetScore(std::string n, int r) {
    //Pre: la funció Init() ha estat cridada abans (és a dir el vector està ordenat)
    //Posem el nou record sustituint al ultim i tornem a ordenar el vector
    score[MAX_RANK - 1].name = n;
    score[MAX_RANK - 1].rank = r;
    sort(score.begin(), score.end(), cond);
}


void CRanking::SaveScores() {
    std::fstream ranking;
    ranking.open("./data/ranking.txt", std::ios::trunc | std::ios::out);
	for (int i = 0; i < MAX_RANK; i++) {
		ranking << score[i].name << " " << score[i].rank << std::endl;
	}
    ranking.close();
}


void CRanking::ResetRanking() {
	score[0].name = "the";
	score[0].rank = 900000;
	score[1].name = "final";
	score[1].rank = 750000;
	score[2].name = "answer";
	score[2].rank = 300000;
	score[3].name = "to";
	score[3].rank = 100000;
	score[4].name = "life";
	score[4].rank = 50000;
	score[5].name = "universe";
	score[5].rank = 25000;
	score[6].name = "and";
	score[6].rank = 10000;
	score[7].name = "everything";
	score[7].rank = 1000;
	score[8].name = "is";
	score[8].rank = 100;
	score[9].name = "42";
	score[9].rank = 42;
}

void CRanking::draw(){

	//definicio de la matriu de projeccio en ortho per al fons
	CGraphics::pGetInstance()->canviaOrthoView();

	//dbuixem fons
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, imatge_rank);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, float(RES_V), 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(float(RES_H), float(RES_V), 0.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(float(RES_H), 0.0f, 0.0f);
	glEnd();

	//Capçalera
	escriptor->escriu(224, 32, 1.0f, "high scores");

	//Escribim el ranking
	for (int i = 0; i < MAX_RANK; i++) {
		std::string p= "";
		int punts = score[i].rank;
		int j;
		for (j = 5; punts > 0 && j >= 0; j--) {
			std::string s = "0";
			s[0] += punts%10;
			p = s+p;
			punts = punts/10;
		}

		escriptor->escriu(114, 100 + i*50, 1.0f, score[i].name);
		escriptor->escriu(494+j*32, 100 + i*50, 1.0f, p);
	}
	glDisable(GL_TEXTURE_2D);

	CGraphics::pGetInstance()->tornaOrthoView();
}

void CRanking::update(float time) {
	//de moment res
}