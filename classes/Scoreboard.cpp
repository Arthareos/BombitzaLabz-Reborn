#include "Scoreboard.h"

Scoreboard::Scoreboard() {}

Scoreboard::Scoreboard(Map& map, Player& player, int time)
{
	this->m_score = player.GetScore();
	this->m_highscore = player.GetHighscore();
	this->m_lives = player.GetLives();
	this->m_clock.restart();
	this->m_roundLenght = time;

	sf::RectangleShape aux(sf::Vector2f(960, 64));
	sf::Vector2f mapCenter(map.GetMapTiles().at(0).at(0).GetCoordinates().first / 2, map.GetMapTiles().at(0).at(0).GetCoordinates().second);
	aux.setPosition(mapCenter.x, mapCenter.y - 64);
	aux.setFillColor(sf::Color::Color(sf::Uint8(117), sf::Uint8(228), sf::Uint8(255), sf::Uint8(255)));

	m_wrapper = aux;
}

void Scoreboard::draw(sf::RenderWindow& window, float deltaTime)
{
	m_wrapper.setPosition(window.getView().getCenter().x - window.getView().getSize().x / 2, window.getView().getCenter().y - window.getView().getSize().y / 2);
	window.draw(m_wrapper);

	std::string string = "[ Score " + std::to_string(m_score) + " ]";
	m_text.getText().setString(string);
	sf::FloatRect textRect = m_text.getText().getLocalBounds();
	m_text.getText().setOrigin(textRect.left, textRect.top);
	m_text.getText().setPosition(sf::Vector2f(m_wrapper.getGlobalBounds().left + 7.5, m_wrapper.getGlobalBounds().top + 7.5));
	window.draw(m_text.getText());

	string = "[ Hiscore " + std::to_string(m_highscore) + " ]";
	m_text.getText().setString(string);
	textRect = m_text.getText().getLocalBounds();
	m_text.getText().setOrigin(textRect.left, textRect.top);
	m_text.getText().setPosition(sf::Vector2f(m_wrapper.getGlobalBounds().left + 7.5, m_wrapper.getGlobalBounds().top + m_wrapper.getLocalBounds().height - m_text.getText().getLocalBounds().height - 7.5));
	window.draw(m_text.getText());

	//Clock implementation
	int aux = m_roundLenght - m_clock.getElapsedTime().asSeconds();
	string = "[ " + std::to_string(aux) + " ]";
	m_text.getText().setString(string);
	textRect = m_text.getText().getLocalBounds();
	m_text.getText().setOrigin(textRect.left, textRect.top);
	m_text.getText().setPosition(sf::Vector2f(m_wrapper.getGlobalBounds().left + m_wrapper.getGlobalBounds().width / 2 - textRect.width / 2, m_wrapper.getGlobalBounds().top + m_wrapper.getSize().y / 2 - textRect.height / 2));
	window.draw(m_text.getText());

	string = "[ Lives " + std::to_string(m_lives) + " ]";
	m_text.getText().setString(string);
	textRect = m_text.getText().getLocalBounds();
	m_text.getText().setOrigin(textRect.left, textRect.top);
	m_text.getText().setPosition(sf::Vector2f(m_wrapper.getGlobalBounds().left + m_wrapper.getGlobalBounds().width - textRect.width - 7.5, m_wrapper.getGlobalBounds().top + m_wrapper.getSize().y / 2 - textRect.height / 2));
	window.draw(m_text.getText());
}

void Scoreboard::AddScore(uint64_t& score)
{
	this->m_score += score;
}

void Scoreboard::SetHighscore()
{
	if (m_score > m_highscore)
	{
		m_highscore = m_score;
	}
}

void Scoreboard::SetTimer(int16_t& seconds)
{
	m_roundLenght = seconds;
}

void Scoreboard::SetLives(uint16_t& lives)
{
	this->m_lives = lives;
}

const uint64_t& Scoreboard::GetScore()
{
	return m_score;
}

const uint64_t& Scoreboard::GetHighscore()
{
	return m_highscore;
}

const int16_t& Scoreboard::GetElapsedTime()
{
	return m_clock.getElapsedTime().asSeconds();
}

//Returns it as seconds
const int16_t& Scoreboard::GetRemainingTime()
{
	return m_roundLenght - m_clock.getElapsedTime().asSeconds();
}

const uint16_t& Scoreboard::GetLives()
{
	return m_lives;
}