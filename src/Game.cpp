#include "Game.h"


CGame::CGame() {
}

CGame::~CGame(){
}


bool CGame::Init(){    

	//Delete console
	#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
	#pragma comment(lib,"glaux.lib")

	if (SDL_Init(0) == -1) return false;

    //iniciem els motors
	graphics = CGraphics::pGetInstance();
	if (!graphics->bInit()) return false;

	//INIT EMYL
	emyl::manager* musicman = emyl::manager::get_instance();
	if(!musicman->init()) return false;
	//iniciem amb la musica del menu
	menuMusic = new emyl::stream();
	menuMusic->load("./data/music/menu.ogg");
	menuMusic->set_loop(true);
	menuMusic->set_source();
	menuMusic->play();

	//preparem la del joc
	gameMusic = new emyl::stream();
	gameMusic->load("./data/music/game.ogg");
	gameMusic->set_loop(true);

	//carreguem els sons
	soundman = CSoundManager::pGetInstance();
	soundman->loadSounds();

	//iniciar input
	input = CInput::pGetInstance();

	//iniciar menu, ranking i credits
	menu = CMenu::pGetInstance();
	menu->init();
	ranking = new CRanking();
	ranking->init();
	credits = new CCredits();

	//iniciar l'escena
	escena = CScene::pGetInstance();

	//parametres
	bExit = false;
	soActiu = true;
	gameState = GS_MENU;
	
	srand(time(NULL));

	return true;
}
    
    
void CGame::GameLoop(){
    float time = input->getGlobalTime();
	
	while(!bExit) {
        //INPUT
		int tics = SDL_GetTicks();
		time = input->getGlobalTime();
		input->update();

		//LOGICA
		switch(gameState) {
			case GS_LOGO:
				break;
			case GS_MENU: {
				int opcio = menu->update(input->getGlobalTime()-time);
				switch(opcio) {
					case MB_PLAY:
						gameState = GS_PLAY;
						posaMusicaGame(false);
						break;
					case MB_NEWGAME: {
						gameState = GS_PLAY;
						menu->setContinuar(true);
						posaMusicaGame(true);
						escena->init();
						soundman->play(SO_INICI);
						}
						break;
					case MB_RANKING:
						ranking->init();
						gameState = GS_RANKING;
						break;
					case MB_CREDITS:
						credits->init();
						gameState = GS_CREDITS;
						break;
					case MB_EXIT:
						menuMusic->free_source();
						End();
						break;
					default:
						break;
				}
				break;
			}
			case GS_PLAY:
				if (escena->gameOver()) {
					gameMusic->pause();
					soundman->play(SO_GAMEOVER);
					menu->setContinuar(false);
					gameState = GS_GAMEOVER;
					int punts = escena->getPuntuacio();
					if (ranking->CheckScore(punts)) {
						ranking->SetScore("player", punts);
						ranking->SaveScores();
					}
				}
				if (input->checkPress(kEsc)) {
					posaMusicaMenu();
					soundman->stopAll();
					menu->reset();
					gameState = GS_MENU;
				}
				if (input->checkPress(kEnter)) {
					gameMusic->pause();
					gameState = GS_PAUSE;
				}
				escena->doStep((input->getGlobalTime()-time));
				break;
			case GS_PAUSE:
				if (input->checkPress(kEsc)) {
					posaMusicaMenu();
					gameState = GS_MENU;
					menu->reset();
				}
				if (input->checkPress(kEnter)) {
					gameState = GS_PLAY;
					gameMusic->play();
				}
				break;
			case GS_GAMEOVER:
				if (input->checkPress(kEsc)) {
					posaMusicaMenu();
					gameState = GS_RANKING;
				}
				break;
			case GS_RANKING:
				ranking->update(time);
				if (input->checkPress(kEsc) || input->checkPress(kEnter)) {
					ranking->SaveScores();
					gameState = GS_MENU;
					menu->reset();
				}
				break;
			case GS_CREDITS:
				if (input->checkPress(kEsc) || input->checkPress(kEnter)) {
					gameState = GS_MENU;
					menu->reset();
				}
				break;
			default:
				break;
		}

		//activar/desactivar so

		if (input->checkPress(kSound))  {
			soActiu = !soActiu;
			float volum;
			if (soActiu) volum = 1.0f;
			else volum = 0.0f;
			emyl::manager::get_instance()->set_volume(volum);
		}

		//omplir buffers
		emyl::stream::updateAll();
		//dibuixar
		this->draw();

		int tics2 = SDL_GetTicks() - tics;
		if(tics2 < 10) SDL_Delay(10-tics2);
	}
}


void CGame::draw() {
	//DIBUIXAR SEGONS L'ESTAT
	switch(gameState) {
		case GS_LOGO:
			break;
		case GS_MENU: {
            menu->draw();
            graphics->flip();
			break;
		}
		case GS_PLAY:
			escena->drawScene();
			graphics->flip();
			break;
		case GS_PAUSE:
			escena->drawScene();
			graphics->canviaOrthoView();
			CWriter::getInstance()->escriu(RES_H/2-80, RES_V/2-16, 1.0f, "pause");
			graphics->tornaOrthoView();
			graphics->flip();
			break;
		case GS_GAMEOVER:
			escena->drawScene();
			graphics->canviaOrthoView();
			CWriter::getInstance()->escriu(RES_H/2-144, RES_V/2-16, 1.0f, "game over");
			graphics->tornaOrthoView();
			graphics->flip();
			break;
		case GS_RANKING:
			ranking->draw();
			graphics->flip();
			break;
		case GS_CREDITS:
			credits->draw();
			graphics->flip();
			break;
		default:
			break;
	}
	SDL_Delay(1);
}


void CGame::End() {
	//tancar tot allo necessari
	//emyl::manager::~manager();
	bExit = true;
}


void CGame::posaMusicaMenu() {
	gameMusic->free_source();
	soundman->stopAll();
	menuMusic->set_source();
	menuMusic->load("./data/music/menu.ogg");
	menuMusic->play();
}

void CGame::posaMusicaGame(bool init) {
	menuMusic->free_source();
	gameMusic->set_source();
	if (init) gameMusic->load("./data/music/game.ogg");//gameMusic->seek(0);
	gameMusic->play();
}
