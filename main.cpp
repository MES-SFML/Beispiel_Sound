#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> // Sound Header
#include<string>
using namespace sf; 

int main() {
	int mx = 0;    
	int speed = 1; 

	////////////// Sound /////////////////////////////
	// lade eine Sounddatei (darf nicht zu groß sein)
	sf::SoundBuffer soundLaser;
	if (!soundLaser.loadFromFile("Sound/laser.wav"))
		return -1;

	sf::SoundBuffer soundTreffer;
	if (!soundTreffer.loadFromFile("Sound/treffer.wav"))
		return -1;

	// erstellt eine Objekt mit dem Sound
	sf::Sound sl(soundLaser);
	sf::Sound st(soundTreffer);
	
	////////////// Musik /////////////////////////////
	// Load an ogg music file
	sf::Music music;
	if (!music.openFromFile("Sound/raumschiff.wav"))
		return -1;

	music.play(); // spielt Musik ab 

	RenderWindow window(VideoMode(800, 200), "Laser ");  
	window.setFramerateLimit(60);                       

	
	Font font;
	font.loadFromFile("fonts/arial.ttf");

	
	Text text("", font);

	
	RectangleShape laser(Vector2f(40, 1)); 
	laser.setFillColor(Color::Red);
	laser.setPosition(0, 100);

	
	Text position("", font);
	position.setCharacterSize(15);

	
	while (window.isOpen()) {    

		Vector2f laserPos = laser.getPosition();


		position.setPosition(10, 150); 
		position.setString(
			"laser: X " + std::to_string((int)laserPos.x) + " Y " + std::to_string((int)laserPos.y) + '\n' +
			"Speed: X " + std::to_string(mx) + " Y " + std::to_string(0) + " drücke links / rechts auf der Tastatur!"); // Debug-Ausgabe


		laser.move(mx, 0); 

		
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			mx = --speed;
			sl.play(); // spielt das Soundobjekt "Laser" ab
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			mx = ++speed;
			sl.play(); // spielt das Soundobjekt "Laser" ab
		}
		
		if (laserPos.x < 650) { // Sound ist nicht optimal
			st.play(); // spielt das Soundobjekt "Treffer" ab
		}

		if (laserPos.x >= 800) {
			laser.setPosition(0, 100);
		}

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

	
		window.clear();
		window.draw(laser);
		window.draw(text);
		window.draw(position);
		window.display();
	}
	return 0;
}