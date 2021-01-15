
#include <iostream>
#include <fstream>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"

#include "Collision.h"
#include "random.h"
#include "projectile.h"
#include "player.h"
#include "Entity.h"
#include "Enemy.h"
#include "textDisplay.h"
#include "pickup.h"
#include "Wall.h"

using namespace std;

int main()
{

	//	Variables
	int counter = 0;
	int counter2 = 0;
	int playerScore = 0;
	int currentEnemy = 0;
	int currentEnemy2 = 0;
	int currentEnemy3 = 0;

	//	Menu Variables	++++
	int activeButton = 0;
	int state = 0;
	bool isPlaying = false;

	std::vector<std::string> buttonText{ "Start", "Score", "Quit" };

	//	Player Score
	std::ofstream fileWriter;
	std::ifstream fileReader;
	std::map<int, std::string> score;

	sf::String playerInput;
	std::string word;


	//	Clock
	sf::Clock clock;
	sf::Clock clock2;
	sf::Clock clock3;
	sf::Clock clockEnemy2;
	sf::Clock clockBoss;

	//	Window Setup
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "The Defender!",sf::Style::Fullscreen);
	//sf::Window App(sf::VideoMode(1080, 720, 32), "The Defender!");

	//	Mouse Cursor Visible
	window.setMouseCursorVisible(false);

	//	Set Framerate Limit
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(false);

	//	view
	sf::View view(window.getDefaultView());
	view.zoom(0.7);


	//	Map & Texture
	sf::Texture MapTexture;
	sf::Texture MenuTexture;
	if (!MapTexture.loadFromFile("Image/Maps/Map1.png"))
	{
		cout << "MapBG Load Error" << endl;
	}
	if (!MenuTexture.loadFromFile("Image/Maps/menuBg.jpg"))
	{
		cout << "MenuBG Load Error" << endl;
	}
	sf::Sprite Background;
	sf::Sprite menuBackground;
	Background.setScale(2.f, 2.f);
	Background.setTexture(MapTexture);
	menuBackground.setTexture(MenuTexture);
	menuBackground.setScale(1.9, 1.7);


	//	Music Background
	sf::Music music;
	sf::Music menuMusic;
	if (!menuMusic.openFromFile("Sound/MenuBG.ogg")) {
		cout << "Menu Music Load Error" << endl;
	}
 	if (!music.openFromFile("Sound/ingameMusic.ogg")) {
		cout << "Main Music Load Error" << endl;
	}
	music.setLoop(true);

	menuMusic.setLoop(true);
	//music.play();
	menuMusic.play();

	//Sound Effect
	sf::SoundBuffer buffer;
	sf::SoundBuffer laserShot;
	sf::SoundBuffer biteSound;
	sf::SoundBuffer pickupSound;
	sf::SoundBuffer fireball;
	sf::SoundBuffer burn;
	sf::SoundBuffer dripSound;
	sf::SoundBuffer confirmSound;
	sf::SoundBuffer coinSound;
	if (!buffer.loadFromFile("Sound/hit.wav")) {
		cout << "Sound Load Error" << endl;
	}
	if (!laserShot.loadFromFile("Sound/laser shot.wav")) {
		cout << "Laser Sound Load Error" << endl;
	}
	if (!biteSound.loadFromFile("Sound/punch.wav")) {
		cout << "Punch Sound Load Error" << endl;
	}
	if (!pickupSound.loadFromFile("Sound/pickup.wav")) {
		cout << "PickUp Sound Load Error" << endl;
	}
	if (!fireball.loadFromFile("Sound/fireball.wav")) {
		cout << "Fireball Sound Load Error" << endl;
	}
	if (!burn.loadFromFile("Sound/burn.wav")) {
		cout << "Burn Sound Load Error" << endl;
	}
	if (!dripSound.loadFromFile("Sound/drip.wav")) {
		cout << "Drip Sound Load Error" << endl;
	}
	if (!confirmSound.loadFromFile("Sound/confirm.wav")) {
		cout << "Confirm Sound Load Error" << endl;
	}
	if (!coinSound.loadFromFile("Sound/coin.wav")) {
		cout << "Sound Load Error" << endl;
	}

	sf::Sound hit;
	sf::Sound shoot;
	sf::Sound bite;
	sf::Sound pickSound;
	sf::Sound enemyShot;
	sf::Sound burnSound;
	sf::Sound seleteSound;
	sf::Sound enterSound;
	sf::Sound scoreSound;
	hit.setBuffer(buffer);
	shoot.setBuffer(laserShot);
	bite.setBuffer(biteSound);
	pickSound.setBuffer(pickupSound);
	enemyShot.setBuffer(fireball);
	burnSound.setBuffer(burn);
	seleteSound.setBuffer(dripSound);
	enterSound.setBuffer(confirmSound);
	scoreSound.setBuffer(coinSound);

	//	Create a graphical text to display
	sf::Font font;
	sf::Font titleFont;
	if (!font.loadFromFile("Image/Font1.ttf"))
	{
		cout << "Main Font Load Error" << endl;
	}
	if (!titleFont.loadFromFile("Image/fontTitle.ttf"))
	{
		cout << "Title Font Load Error" << endl;
	}
	sf::Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(40);

	sf::Text textHp;
	textHp.setFont(font);
	textHp.setCharacterSize(40);


	//	Player Texture
	sf::Texture texturePlayer;
	if (!texturePlayer.loadFromFile("Image/Player.png")) {
		cout << "load player texture failed" << endl;
	}
	sf::Sprite spritePlayer(texturePlayer);
	//spritePlayer.setPosition(window.getSize().x/2, window.getSize().y/2);
	

	//	Enemy1 Texture
	sf::Texture textureEnemy;
	if (!textureEnemy.loadFromFile("Image/Enemy1.png")) {
		cout << "load Enemy1 texture failed" << endl;
	}
	//	Enemy2 Texture
	sf::Texture textureEnemy2;
	if (!textureEnemy2.loadFromFile("Image/Enemy2.png")) {
		cout << "load Enemy2 texture failed" << endl;
	}
	//	Enemy3 Texture
	sf::Texture textureEnemy3;
	if (!textureEnemy3.loadFromFile("Image/EnemyBoss.png")) {
		cout << "load Enemy3 texture failed" << endl;
	}


	//	Shooting Effect Texture
	sf::Texture textureShot;
	if (!textureShot.loadFromFile("Image/Effect/Magic.png")) {
		cout << "load Magic texture failed" << endl;
	}
	sf::Texture textureShot2;
	if (!textureShot2.loadFromFile("Image/Effect/Magic2.png")) {
		cout << "load Magic2 texture failed" << endl;
	}


	//	PowerUP Texture
	sf::Texture texturePowerup;
	if (!texturePowerup.loadFromFile("Image/Ball.png")) {
		cout << "load PowerUp texture failed" << endl;
	}
	//	Health Texture
	sf::Texture textureHealth;
	if (!textureHealth.loadFromFile("Image/Health.png")) {
		cout << "Health load texture failed" << endl;
	}

	//	Pickup Vector Array
	vector<pickup>::const_iterator iterPickup;
	vector<pickup> pickupArray;

	//	Pickup Object
	class pickup pickup1;
	pickup1.sprite.setTexture(texturePowerup);

	class pickup pickHp;
	pickHp.sprite.setTexture(textureHealth);



	//	Class Object
	class player Player1;
	Player1.sprite.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	Player1.sprite.setTexture(texturePlayer);



	//	Projectile Vector Array
	vector<projectile>::const_iterator iter;
	vector<projectile> projectileArray;

	//	Projectile Object
	class projectile projectile1;
	projectile1.sprite.setTexture(textureShot);



	//	Enemy Vector Array
	vector<Enemy>::const_iterator iterEnemy;
	vector<Enemy> enemyArray;

	//	Enemy 1 Object
	class Enemy Enemy1;
	Enemy1.sprite.setTexture(textureEnemy);
	Enemy1.hp = 3;
	Enemy1.isEnemy = 1;
	Enemy1.enemyLimit = 10;
	Enemy1.attackDamage = 2;
	Enemy1.movementSpeed = 2;
	Enemy1.moventLength = 200;
	//enemyArray.push_back(Enemy1);

	//	Enemy 2
	class Enemy Enemy2;
	Enemy2.sprite.setTexture(textureEnemy2);
	Enemy2.hp = 5;
	Enemy2.isEnemy = 2;
	Enemy2.enemyLimit = 5;
	Enemy2.attackDamage = 4;
	Enemy2.movementSpeed = 1.5;
	Enemy1.moventLength = 300;

	//	Enemy 3 (Boss)
	class Enemy Enemy3;
	Enemy3.sprite.setTexture(textureEnemy3);
	Enemy3.hp = 7;
	Enemy3.isEnemy = 3;
	Enemy3.enemyLimit = 3;
	Enemy3.attackDamage = 6;
	Enemy3.movementSpeed = 2.5;
	Enemy1.moventLength = 300;



	//	Text Vector Array
	vector<textDisplay>::const_iterator iterText;
	vector<textDisplay> textDisplayArray;

	//	Text Display Object
	class textDisplay textDisplay1;
	textDisplay1.text.setFont(font);



	//	Wall Vector Array
	vector<wall>::const_iterator iterwall;
	vector<wall> wallArray;

	class wall wall1;
	wall1.rect.setFillColor(sf::Color::Transparent);



	//	Crate Horizontal Wall
	wall1.rect.setSize(sf::Vector2f(3100, 30));
	wall1.rect.setPosition(280, 600);
	wallArray.push_back(wall1);

	wall1.rect.setPosition(280, 1420);
	wallArray.push_back(wall1);

	//	Crate Vertical Wall

	wall1.rect.setSize(sf::Vector2f(30, 900));
	wall1.rect.setPosition(260, 600);
	wallArray.push_back(wall1);

	wall1.rect.setPosition(3320, 600);
	wallArray.push_back(wall1);


	while (window.isOpen())		// WINDOW Open
	{
		//	Game Window Event
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		//	Clear screen
		window.clear();

		//	Back to Menu State ++++++;;;;
		if (!isPlaying) {
			window.setView(sf::View({ 1920 / 2, 1080 / 2 }, { 1920, 1080 }));
			window.clear(sf::Color(186, 225, 255));

			//	Menu Background
			window.draw(menuBackground);

			sf::Text text("NONTAPAN RUJIRAKAL [62010453]", font);
			text.setFont(titleFont);
			text.setCharacterSize(40);
			text.setFillColor(sf::Color::White);
			//text.setOutlineThickness(3);
			text.setOutlineColor(sf::Color::Black);
			text.setPosition(1200, 1000);
			window.draw(text);

			if (state == 0) {

				//	Game Title
				sf::Text text("The Defender", font);
				text.setFont(titleFont);
				text.setCharacterSize(150);
				text.setFillColor(sf::Color::Black);
				text.setPosition(275, 145);
				window.draw(text);

				text.setFillColor(sf::Color::White);
				text.setOutlineThickness(7);
				text.setOutlineColor(sf::Color::Black);
				text.setPosition(260, 130);
				window.draw(text);


				//	Menu Button
				for (int button = 0; button < 3; button++) {
					sf::Text text(buttonText.at(button), font);
					text.setCharacterSize(65);
					text.setFillColor(sf::Color::White);
					text.setOutlineThickness(3);
					text.setOutlineColor(sf::Color::Black);
					if (button == activeButton) {
						text.setStyle(sf::Text::Bold);
						text.setFillColor(sf::Color::Red);
					}
					text.setPosition(290, 420 + 140 * button);
					window.draw(text);
				}
			}
			if (state == 1) {
				//	Show Score
				sf::Text text("Enter", font);
				text.setCharacterSize(50);
				text.setFillColor(sf::Color::White);
				text.setOutlineThickness(3);
				text.setOutlineColor(sf::Color::Black);

				fileReader.open("Save/score.txt");
				do {
					fileReader >> word;
					auto first_token = word.substr(0, word.find(','));
					auto second_token = std::stoi(word.substr(word.find(',') + 1, word.length()));
					score[second_token] = first_token;
				} while (fileReader.good());
				fileReader.close();

				std::map<int, std::string>::iterator end = score.end();
				std::map<int, std::string>::iterator beg = score.begin();
				end--;
				beg--;

				int currentDisplay = 0;
				for (std::map<int, std::string>::iterator it = end; it != beg; it--) {
					text.setString(it->second);
					text.setPosition(450, 270 + 110 * currentDisplay);
					window.draw(text);
					text.setString(std::to_string(it->first));
					text.setPosition(1300, 270 + 110 * currentDisplay);
					window.draw(text);
					currentDisplay++;
					if (currentDisplay == 5) {
						break;
					}
				}
				currentDisplay = 0;

				text.setOutlineThickness(5);
				text.setCharacterSize(90);
				text.setFont(titleFont);
				text.setString("High Score");	//	High Score
				text.setPosition(700, 80);
				window.draw(text);

				text.setFont(font);
				text.setOutlineThickness(0);
				text.setCharacterSize(40);
				text.setString("Press Enter to Main Menu");	//	Back to Main Menu
				text.setPosition(690, 860);
				window.draw(text);
			}
			if (state == 2) {
				//	Game Over
				sf::Text text("Game Over", font);
				sf::RectangleShape nameShape;
				nameShape.setFillColor(sf::Color::White);
				nameShape.setOutlineThickness(1);
				nameShape.setOutlineColor(sf::Color::Green);
				nameShape.setSize(sf::Vector2f(450,80));
				nameShape.setPosition(740,620);
				window.draw(nameShape);

				text.setFillColor(sf::Color::Yellow);
				text.setLetterSpacing(2);
				text.setCharacterSize(120);
				text.setOutlineThickness(4);
				text.setFont(titleFont);
				text.setString("Game Over");
				text.setPosition(550, 150);
				window.draw(text);

				text.setFillColor(sf::Color::White);
				text.setCharacterSize(60);
				text.setOutlineThickness(3);
				text.setFont(font);
				text.setString("Your Score: " + to_string(playerScore));
				text.setPosition(680, 400);
				window.draw(text);

				text.setFillColor(sf::Color::Green);
				text.setOutlineThickness(2);
				text.setCharacterSize(40);
				text.setString("-- Enter Your Name --");
				text.setPosition(730, 550);
				window.draw(text);

				text.setLetterSpacing(1);
				text.setFillColor(sf::Color::White);
				text.setOutlineThickness(2);
				text.setCharacterSize(40);
				text.setString(playerInput);
				text.setPosition(770, 630);
				window.draw(text);

				text.setLetterSpacing(2);
				text.setFont(font);
				text.setOutlineThickness(0);
				text.setCharacterSize(40);
				text.setString("Press Enter to Main Menu");	//	Back to Main Menu
				text.setPosition(690, 860);
				window.draw(text);
			}

			window.display();

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {

						enterSound.play();

						if (state == 0) {
							if (activeButton == 0) {
								isPlaying = true;

								std::cout << "start playing" << std::endl;

								//	Clear for New Game
								window.clear();
								Player1.hp = Player1.hpMax;
								enemyArray.clear();
								pickupArray.clear();
								projectileArray.clear();
								textDisplayArray.clear();
								currentEnemy = 0;
								currentEnemy2 = 0;
								currentEnemy3 = 0;

								//	Setting for New Game
								Player1.rect.setPosition(1850, 700);
								Player1.powerup = false;

								menuMusic.stop();
								music.stop();

								music.play();

							}
							if (activeButton == 1) {
								state = 1;
							}
							if (activeButton == 2) {
								return 0;
							}
						}
						else if (state == 1) {
							state = 0;
						}
						else if (state == 2) {
							std::cout << "enter" << std::endl;
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						activeButton--;
						if (activeButton < 0) {
							activeButton = 2;
						}
						if (state == 0)
						{
							seleteSound.play();
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						activeButton++;
						if (activeButton > 2) {
							activeButton = 0;
						}
						if (state == 0)
						{
							seleteSound.play();
						}
					}
				}
				if (event.type == sf::Event::Closed) {
					return 0;
				}
				if (event.type == sf::Event::TextEntered && state == 2) {
					if (event.text.unicode == 13) { //	Enter
						fileWriter.open("save/score.txt", std::ios::out | std::ios::app);
						fileWriter << playerInput.toAnsiString() << "," << playerScore << '\n';
						fileWriter.close();
						playerInput.clear();
						state = 0;
						playerScore = 0;
					}
					if (event.text.unicode == 8) { //	Backspace
						playerInput = playerInput.substring(0, playerInput.getSize() - 1);
					}
					else {
						playerInput += event.text.unicode;
					}
				}
			}
		}
		else
		{
			//	Clock screen
			sf::Time elapsed1 = clock.getElapsedTime();
			sf::Time elapsed2 = clock2.getElapsedTime();
			sf::Time elapsed3 = clock3.getElapsedTime();
			sf::Time elapsedEnemy2 = clockEnemy2.getElapsedTime();
			sf::Time elapsedBoss = clockBoss.getElapsedTime();

			//	Draw Background
			window.clear(sf::Color(41, 152, 241));
			window.draw(Background);

			//	Draw Wall
			counter = 0;
			for (iterwall = wallArray.begin(); iterwall != wallArray.end(); iterwall++)
			{
				window.draw(wallArray[counter].rect);
				counter++;
			}

			//	Enemy Collides with Wall
			counter = 0;
			for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++)
			{
				counter2 = 0;
				for (iterwall = wallArray.begin(); iterwall != wallArray.end(); iterwall++)
				{
					if (enemyArray[counter].rect.getGlobalBounds().intersects(wallArray[counter2].rect.getGlobalBounds()))
					{
						//	Hit Wall
						if (enemyArray[counter].direction == 1)	//	Up Check
						{
							enemyArray[counter].canMoveUp = false;
							enemyArray[counter].rect.move(0, 0.5);
						}
						if (enemyArray[counter].direction == 2)	//	Down Check
						{
							enemyArray[counter].canMoveDown = false;
							enemyArray[counter].rect.move(0, -0.5);
						}
						if (enemyArray[counter].direction == 3)	//	Left Check
						{
							enemyArray[counter].canMoveLeft = false;
							enemyArray[counter].rect.move(0.5, 0);
						}
						if (enemyArray[counter].direction == 4)	//	Right Check
						{
							enemyArray[counter].canMoveRight = false;
							enemyArray[counter].rect.move(-0.5, 0);
						}
						else
						{

						}
					}
					counter2++;
				}
				counter++;
			}

			//	Player Collides with Wall
			counter = 0;
			for (iterwall = wallArray.begin(); iterwall != wallArray.end(); iterwall++)
			{
				if (Player1.rect.getGlobalBounds().intersects(wallArray[counter].rect.getGlobalBounds()))
				{
					//	Hit Wall
					if (Player1.side == 4)	//	Up Check
					{
						Player1.canMoveUp = false;
						Player1.rect.move(0, 1);
					}
					if (Player1.side == 3)	//	Down Check
					{
						Player1.canMoveDown = false;
						Player1.rect.move(0, -1);
					}
					if (Player1.direction == 2)	//	Left Check
					{
						Player1.canMoveLeft = false;
						Player1.rect.move(1, 0);
					}
					if (Player1.direction == 1)	//	Right Check
					{
						Player1.canMoveRight = false;
						Player1.rect.move(-1, 0);
					}
					else
					{

					}
				}
				counter++;
			}

			//	Player collides with Pickup Item
			counter = 0;
			for (iterPickup = pickupArray.begin(); iterPickup != pickupArray.end(); iterPickup++)
			{
				if (Collision::PixelPerfectTest(Player1.sprite, pickupArray[counter].sprite))
				{
					if (pickupArray[counter].isPowerup == true)
					{
						Player1.powerup = true;

						//	Text "Fire Ball"
						textDisplay1.text.setFillColor(sf::Color::Yellow);
						textDisplay1.text.setOutlineColor(sf::Color::Black);
						textDisplay1.text.setString("FIRE BALL !");
						textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 1.5, Player1.rect.getPosition().y - 24);
						textDisplayArray.push_back(textDisplay1);

						pickupArray[counter].destroy = true;
					}
					if (pickupArray[counter].isHealth == true)
					{
						if (Player1.hp > 95)
						{
							Player1.hp = 100;
							textDisplay1.text.setString("HP Max");
						}
						else
						{
							Player1.hp += 5;
							textDisplay1.text.setString("HP + 5");
						}

						//	Text "Healing"
						textDisplay1.text.setFillColor(sf::Color::Magenta);
						textDisplay1.text.setOutlineColor(sf::Color::Black);
						textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 1.5, Player1.rect.getPosition().y - 24);
						textDisplayArray.push_back(textDisplay1);

						pickupArray[counter].destroy = true;

					}
					pickSound.play();
				}
				counter++;
			}


			//	Enemy Collides with Player (Player takes damage)
			if (elapsed2.asSeconds() >= 0.3)
			{
				clock2.restart();
				counter = 0;
				for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++)
				{
					if (Collision::PixelPerfectTest(Player1.sprite, enemyArray[counter].sprite))
						//if(Player1.rect.getGlobalBounds().intersects(enemyArray[counter].rect.getGlobalBounds()))
					{
						cout << "Enemy Hit Player" << endl;

						//	Text Display
						textDisplay1.text.setFillColor(sf::Color::Red);
						textDisplay1.text.setString(to_string(enemyArray[counter].attackDamage));
						textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2, Player1.rect.getPosition().y - 24);
						textDisplayArray.push_back(textDisplay1);

						bite.play();	//	Play bite Sound Effect

						Player1.hp -= enemyArray[counter].attackDamage;
						if (Player1.hp <= 0) {
							isPlaying = false;

							state = 2;

							menuMusic.stop();
							music.stop();
							menuMusic.play();
						}

						Player1.powerup = false;
					}
					counter++;
				}
			}

			//	Enemy Attack (AI)
			counter = 0;
			for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++)
			{
				if (elapsed3.asSeconds() >= 1)
				{
					clock3.restart();

					int tempRand = generateRandom(3);

					if (enemyArray[counter].isEnemy == 2 || enemyArray[counter].isEnemy == 3)	//	Enemy Fires Projectile at Player & Chases Player
					{
						//Player to Left 
						if ((Player1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x) && (abs(Player1.rect.getPosition().y - enemyArray[counter].rect.
							getPosition().y) <= 35))
						{
							projectile1.direction = 2;
							projectile1.lifeTime = 150;
							projectile1.movementSpeed = 3;
							projectile1.sprite.setTexture(textureShot2);
							projectile1.enemyProjectile = true;
							projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x - 40, enemyArray[counter].rect.getPosition().y + 30);
							projectileArray.push_back(projectile1);
							projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 3;
							enemyShot.play();
						}
						//	Player to Right
						if ((Player1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x) && (abs(Player1.rect.getPosition().y - enemyArray[counter].rect.
							getPosition().y) <= 35))
						{
							projectile1.direction = 1;
							projectile1.lifeTime = 150;
							projectile1.movementSpeed = 3;
							projectile1.sprite.setTexture(textureShot2);
							projectile1.enemyProjectile = true;
							projectile1.rect.setPosition(enemyArray[counter].rect.getPosition().x + 60, enemyArray[counter].rect.getPosition().y + 30);
							projectileArray.push_back(projectile1);
							projectile1.enemyProjectile = false;

							enemyArray[counter].direction = 4;
							enemyShot.play();
						}
					}
					if (tempRand == 2)  //	Enemy Chases Player
					{
						if (Player1.rect.getPosition().y < enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 2;
						}
						else if (Player1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 4;
						}
					}
					else  //	Enemy Chases Player
					{
						if (Player1.rect.getPosition().x < enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 3;
						}
						else if (Player1.rect.getPosition().x > enemyArray[counter].rect.getPosition().x)
						{
							enemyArray[counter].direction = 4;
						}
						else if (Player1.rect.getPosition().y < enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 1;
						}
						else if (Player1.rect.getPosition().y > enemyArray[counter].rect.getPosition().y)
						{
							enemyArray[counter].direction = 2;
						}
					}
				}

				counter++;
			}


			//	Projectile Collides with Enemy
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				counter2 = 0;
				for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++)
				{
					if (Collision::PixelPerfectTest(projectileArray[counter].sprite, enemyArray[counter2].sprite))
					{
						if (projectileArray[counter].enemyProjectile == false)
						{
							projectileArray[counter].destroy = true;

							//	Text Display
							textDisplay1.text.setFillColor(sf::Color::Red);
							textDisplay1.text.setString(to_string(projectileArray[counter].attackDamage));
							textDisplay1.text.setPosition(enemyArray[counter2].rect.getPosition().x + enemyArray[counter2].rect.getSize().x / 2, enemyArray[counter2].rect.getPosition().y - 10);
							textDisplayArray.push_back(textDisplay1);

							enemyArray[counter2].hp -= projectileArray[counter].attackDamage;

							hit.play();	//	Hit Sound Effect

							if (enemyArray[counter2].hp <= 0)
							{
								enemyArray[counter2].alive = false;
							}
						}
					}
					counter2++;
				}
				counter++;
			}


			//	Enemy Projectile Collides with Player
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				if (projectileArray[counter].enemyProjectile == true)
				{
					if (Collision::PixelPerfectTest(Player1.sprite, projectileArray[counter].sprite))
					{
						Player1.hp -= 8;
						Player1.powerup = false;

						if (Player1.hp <= 0) {
							isPlaying = false;
							state = 2;
						}

						//	Text Display
						textDisplay1.text.setFillColor(sf::Color::Red);
						textDisplay1.text.setString("8");
						textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2, Player1.rect.getPosition().y - 24);
						textDisplayArray.push_back(textDisplay1);

						burnSound.play();

						projectileArray[counter].destroy = true;
					}
				}
				counter++;
			}




			//	Delete Dead Enemy
			counter = 0;
			for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++)
			{
				if (enemyArray[counter].alive == false)
				{
					cout << "Enemy has been kill" << endl;

					//	Drop 
					if (generateRandom(8) == 1)
					{
						pickup1.isPowerup = true;
						pickup1.sprite.setTexture(texturePowerup);
						pickup1.rect.setPosition(enemyArray[counter].rect.getPosition());
						pickupArray.push_back(pickup1);
					}
					else if (generateRandom(6) == 1)
					{
						pickHp.isHealth = true;
						pickHp.sprite.setTexture(textureHealth);
						pickHp.rect.setPosition(enemyArray[counter].rect.getPosition());
						pickupArray.push_back(pickHp);
					}

					if (enemyArray[counter].isEnemy == 1)	//	if Enemy1 delete
					{
						currentEnemy--;
						playerScore += 100;	//	Get Score

						//	Text Display
						textDisplay1.text.setFillColor(sf::Color::Yellow);
						textDisplay1.text.setString("+100");
						textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2, Player1.rect.getPosition().y);
						textDisplayArray.push_back(textDisplay1);

						scoreSound.play();	// Get Score Effect
					}
					else if (enemyArray[counter].isEnemy == 2)	//	if Enemy2 delete
					{
						currentEnemy2--;
						playerScore += 400; //	Get Score

						//	Text Display
						textDisplay1.text.setFillColor(sf::Color::Yellow);
						textDisplay1.text.setString("+400");
						textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2, Player1.rect.getPosition().y);
						textDisplayArray.push_back(textDisplay1);

						scoreSound.play();	// Get Score Effect
					}
					else if (enemyArray[counter].isEnemy == 3)	//	if EnemyBoss delete
					{
						currentEnemy3--;
						playerScore += 1000; //	Get Score

						//	Text Display
						textDisplay1.text.setFillColor(sf::Color::Yellow);
						textDisplay1.text.setString("+1000");
						textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2, Player1.rect.getPosition().y);
						textDisplayArray.push_back(textDisplay1);

						//	Drop Health
						pickHp.isHealth = true;
						pickHp.sprite.setTexture(textureHealth);
						pickHp.rect.setPosition(enemyArray[counter].rect.getPosition());
						pickupArray.push_back(pickHp);

						scoreSound.play();	// Get Score Effect
					}

					enemyArray.erase(iterEnemy);

					break;
				}
				counter++;
			}

			//	Delete Projectile
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				if (projectileArray[counter].destroy == true)
				{
					projectileArray.erase(iter);
					break;
				}
				counter++;
			}

			//	Delele Text Display
			counter = 0;
			for (iterText = textDisplayArray.begin(); iterText != textDisplayArray.end(); iterText++)
			{
				if (textDisplayArray[counter].destroy == true)
				{
					textDisplayArray.erase(iterText);
					break;
				}
				counter++;
			}

			//	Delete Pickup Item
			counter = 0;
			for (iterPickup = pickupArray.begin(); iterPickup != pickupArray.end(); iterPickup++)
			{
				if (pickupArray[counter].destroy == true)
				{
					pickupArray.erase(iterPickup);
					break;
				}
				counter++;
			}


			//	Spawn Enemy 1 ( Random Position )
			if (currentEnemy < Enemy1.enemyLimit)
			{
				Enemy1.rect.setPosition(400 + generateRandom(2800), 750 + generateRandom(500));
				while(Enemy1.rect.getGlobalBounds().intersects(Player1.rect.getGlobalBounds()))
				{
					Enemy1.rect.setPosition(400 + generateRandom(2800), 750 + generateRandom(500));
				}
				enemyArray.push_back(Enemy1);
				currentEnemy++;
			}

			//	Spawn Enemy 2 ( Random Position )
			if (elapsedEnemy2.asSeconds() > 10.f)
			{
				if (currentEnemy2 < Enemy2.enemyLimit)
				{
					Enemy2.rect.setPosition(400 + generateRandom(2800), 750 + generateRandom(500));
					while (Enemy2.rect.getGlobalBounds().intersects(Player1.rect.getGlobalBounds()))
					{
						Enemy2.rect.setPosition(400 + generateRandom(2800), 750 + generateRandom(500));
					}
					enemyArray.push_back(Enemy2);
					currentEnemy2++;
				}
				clockEnemy2.restart();
			}

			//	Spawn Enemy 3 -[Boss]- ( Random Position & Time )
			if (elapsedBoss.asSeconds() > 20.f)
			{
				if (currentEnemy3 < Enemy3.enemyLimit)
				{
					Enemy3.rect.setPosition(400 + generateRandom(2800), 750 + generateRandom(500));
					while (Enemy3.rect.getGlobalBounds().intersects(Player1.rect.getGlobalBounds()))
					{
						Enemy3.rect.setPosition(400 + generateRandom(2800), 750 + generateRandom(500));
					}
					enemyArray.push_back(Enemy3);
					currentEnemy3++;

				}
				clockBoss.restart();
			}


			//	Enemy Spawn (Key - Y)	+++++++++++++++ Easter Egg +++++++++
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))	
			{
				//Enemy1.rect.setPosition(generateRandom(window.getSize().x), generateRandom(window.getSize().y));
				Enemy1.rect.setPosition(Player1.sprite.getPosition().x + 150, Player1.sprite.getPosition().y + 100);
				enemyArray.push_back(Enemy1);
			}

			//	Include Score (Key - U)	++++++++++++++++ Easter Egg ++++++++
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
			{
				playerScore += 100;

				//	Text Display
				textDisplay1.text.setFillColor(sf::Color::Yellow);
				textDisplay1.text.setString("+100");
				textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2, Player1.rect.getPosition().y);
				textDisplayArray.push_back(textDisplay1);

				scoreSound.play();	// Get Score Effect
			}

			//	Include Health Point (Key - I)	++++++++++++++++ Easter Egg ++++++++
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
			{
				if (Player1.hp < 100)
				{
					Player1.hp += 1;
				}

				//	Text Display
				textDisplay1.text.setFillColor(sf::Color::Magenta);
				textDisplay1.text.setString("HP + 1");
				textDisplay1.text.setPosition(Player1.rect.getPosition().x + Player1.rect.getSize().x / 2, Player1.rect.getPosition().y);
				textDisplayArray.push_back(textDisplay1);
			}


			//	Firing Projectile (Space bar)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (elapsed1.asSeconds() >= 0.2)
				{
					clock.restart();
					if (Player1.powerup == false)
					{
						projectile1.attackDamage = 1;
						projectile1.sprite.setTexture(textureShot);
					}
					else
					{
						projectile1.attackDamage = 3;
						projectile1.sprite.setTexture(textureShot2);
					}

					if (Player1.direction == 1) {
						projectile1.rect.setPosition(Player1.rect.getPosition().x + 50, Player1.rect.getPosition().y + 28);	// Shoot Right Side

					}
					else {
						projectile1.rect.setPosition(Player1.rect.getPosition().x - 35, Player1.rect.getPosition().y + 28); // Shoot Left Side
					}
					shoot.play();	//	Shooting Sound Effect
					projectile1.direction = Player1.direction;
					projectile1.movementSpeed = 7;
					projectile1.lifeTime = 50;
					projectileArray.push_back(projectile1);
				}
			}


			//	Draw Projectiles
			counter = 0;
			for (iter = projectileArray.begin(); iter != projectileArray.end(); iter++)
			{
				projectileArray[counter].update();	//	Update Projectile
				//window.draw(projectileArray[counter].rect);
				window.draw(projectileArray[counter].sprite);
				counter++;
			}

			//	Update Player
			Player1.update();
			Player1.updateMovement();

			//	Draw Player
			window.draw(Player1.sprite);
			//window.draw(Player1.rect);

			//	Draw Pickup Items
			counter = 0;
			for (iterPickup = pickupArray.begin(); iterPickup != pickupArray.end(); iterPickup++)
			{
				pickupArray[counter].update();
				window.draw(pickupArray[counter].sprite);
				counter++;
			}

			//	Draw Enemies
			counter = 0;
			for (iterEnemy = enemyArray.begin(); iterEnemy != enemyArray.end(); iterEnemy++)
			{
				enemyArray[counter].update();
				enemyArray[counter].updateMovement();
				//window.draw(enemyArray[counter].rect);
				window.draw(enemyArray[counter].sprite);
				counter++;
			}

			//	Draw Text
			counter = 0;
			for (iterText = textDisplayArray.begin(); iterText != textDisplayArray.end(); iterText++)
			{
				textDisplayArray[counter].update();
				window.draw(textDisplayArray[counter].text);
				counter++;
			}

			//	Draw Health Point Player
			textHp.setString("HP : " + to_string(Player1.hp) + " / 100");
			textHp.setOutlineThickness(2);
			textHp.setFillColor(sf::Color::White);
			textHp.setOutlineColor(sf::Color::Red);
			window.draw(textHp);
			textHp.setPosition(Player1.rect.getPosition().x - window.getSize().x / 3.3, Player1.rect.getPosition().y - window.getSize().y / 3.5); 

			//	Draw Score
			text.setString("Score : " + to_string(playerScore));
			text.setOutlineColor(sf::Color::Black);
			text.setOutlineThickness(2);
			text.setFillColor(sf::Color::White);
			window.draw(text);
			text.setPosition(Player1.rect.getPosition().x - window.getSize().x / 3.3, Player1.rect.getPosition().y - window.getSize().y / 4.2);

			 
			//	Update the window
			window.display();

			////	Set Character Center View
			view.setCenter(Player1.rect.getPosition().x + 36, Player1.rect.getPosition().y + 36);
			window.setView(view);
		}

	}
	return 0;
}