#include "BattleScoreboard.h"

BattleScoreboard::BattleScoreboard() {}

BattleScoreboard::BattleScoreboard(Map& map, std::vector<BattlePlayer>& players)
{
	this->m_clock.restart();

	sf::RectangleShape aux(sf::Vector2f(960, 64));
	sf::Vector2f mapCenter(map.GetMapTiles().at(0).at(0).GetCoordinates().first / 2, map.GetMapTiles().at(0).at(0).GetCoordinates().second);
	aux.setPosition(mapCenter.x, mapCenter.y - 64);
	aux.setFillColor(sf::Color::Color(sf::Uint8(117), sf::Uint8(228), sf::Uint8(255), sf::Uint8(255)));

	m_wrapper = aux;
}

void BattleScoreboard::Draw(sf::RenderWindow& window, std::vector<BattlePlayer>& players)
{
	m_wrapper.setPosition(window.getView().getCenter().x - window.getView().getSize().x / 2, window.getView().getCenter().y - window.getView().getSize().y / 2);
	window.draw(m_wrapper);

	std::string string = "[ Player 1 / " + std::to_string(players.at(0).GetWins()) + " ]";
	m_text.getText().setString(string);
	sf::FloatRect textRect = m_text.getText().getLocalBounds();
	m_text.getText().setOrigin(textRect.left, textRect.top);
	m_text.getText().setPosition(sf::Vector2f(m_wrapper.getGlobalBounds().left + 7.5, m_wrapper.getGlobalBounds().top + 7.5));
	window.draw(m_text.getText());

	string = "[ Player 2 / " + std::to_string(players.at(1).GetWins()) + " ]";
	m_text.getText().setString(string);
	textRect = m_text.getText().getLocalBounds();
	m_text.getText().setOrigin(textRect.left, textRect.top);
	m_text.getText().setPosition(sf::Vector2f(m_wrapper.getGlobalBounds().left + 7.5, m_wrapper.getGlobalBounds().top + m_wrapper.getLocalBounds().height - m_text.getText().getLocalBounds().height - 7.5));
	window.draw(m_text.getText());

	if (players.size() > 2)
	{
		string = "[ Player 3 / " + std::to_string(players.at(2).GetWins()) + " ]";
		m_text.getText().setString(string);
		textRect = m_text.getText().getLocalBounds();
		m_text.getText().setOrigin(textRect.left, textRect.top);
		m_text.getText().setPosition(sf::Vector2f(m_wrapper.getGlobalBounds().left + m_wrapper.getGlobalBounds().width - textRect.width - 7.5, m_wrapper.getGlobalBounds().top + 7.5));
		window.draw(m_text.getText());

		if (players.size() > 3)
		{
			string = "[ Player 4 / " + std::to_string(players.at(2).GetWins()) + " ]";
			m_text.getText().setString(string);
			textRect = m_text.getText().getLocalBounds();
			m_text.getText().setOrigin(textRect.left, textRect.top);
			m_text.getText().setPosition(sf::Vector2f(m_wrapper.getGlobalBounds().left + m_wrapper.getGlobalBounds().width - textRect.width - 7.5, m_wrapper.getGlobalBounds().top + m_wrapper.getLocalBounds().height - m_text.getText().getLocalBounds().height - 7.5));
			window.draw(m_text.getText());
		}
	}
}