#include "FileProvider.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include "Log.h"

#include "../Ant.h"
#include "../Map.h"
#include "../Cell.h"
#include "../Player.h"

namespace WarAnts
{

FileProvider::FileProvider(const std::string& filename)
	: m_filename(filename)
{
	std::ofstream file(m_filename);

	if (!file.is_open())
	{
		if (!m_cantOpen)
		{
			LOGE("Error: Can create the '%s' log file!", m_filename.c_str());
			m_cantOpen = true;
		}
		return;
	}
	m_cantOpen = false;
}

bool FileProvider::isFileOpen(std::ofstream& of)
{
	if (!of.is_open())
	{
		if (!m_cantOpen)
		{
			LOGE("Error: Can not open the '%s' log file!", m_filename.c_str());
			m_cantOpen = true;
		}
		return false;
	}

	m_cantOpen = false;
	return true;
}

void FileProvider::saveMapInfo(const Map& map)
{
	std::ofstream file(m_filename, std::ios::app);

	if (!isFileOpen(file))
	{
		return;
	}

	nlohmann::json json;

	json["map"]["size"]["width"]  = map.size().x();
	json["map"]["size"]["height"] = map.size().y();

	file << json << std::endl;
	file.close();
}

void FileProvider::savePlayer(const Player& player)
{
	std::ofstream file(m_filename, std::ios::app);

	if (!isFileOpen(file))
	{
		return;
	}

	nlohmann::json json;

	json["player"]["index"] = player.index();
	json["player"]["team"] = player.teamName();
	json["player"]["class"] = player.antClass();
	json["player"]["library"]["filename"] = player.library();
	json["player"]["library"]["hash"] = player.libHash();
	json["player"]["library"]["version"] = player.libVersion();

	file << json << std::endl;
	file.close();
}

void FileProvider::saveBeginTurn(uint32_t iteration)
{
	std::ofstream file(m_filename, std::ios::app);

	if (!isFileOpen(file))
	{
		return;
	}

	nlohmann::json json;

	json["begin"]["iteration"] = iteration;

	file << json << std::endl;

	file.close();
}

void FileProvider::saveEndTurn(uint32_t iteration, size_t msec)
{
	std::ofstream file(m_filename, std::ios::app);

	if (!isFileOpen(file))
	{
		return;
	}

	nlohmann::json json;

	json["end"]["iteration"] = iteration;
	json["end"]["time"] = msec;

	file << json << std::endl;

	file.close();
}

void FileProvider::saveMap(const Map& map)
{
	std::ofstream file(m_filename, std::ios::app);

	if (!isFileOpen(file))
	{
		return;
	}

	uint32_t size = map.size().x() * map.size().y();
	for (uint32_t ii = 0; ii < size; ++ii)
	{
		auto cell = map.cell(ii);
		nlohmann::json json;

		if (!cell->isChanged())
		{
			continue;
		}

		json["cell"]["x"] = ii % map.size().x();
		json["cell"]["y"] = ii / map.size().x();

		if (cell->isEmpty())
		{
			json["cell"]["type"] = "empty";
		}
		else if (cell->isStone())
		{
			json["cell"]["type"] = "stone";
		}
		else if (cell->food())
		{
			json["cell"]["type"] = "food";
			json["cell"]["food"] = cell->food();
		} else
		{
			auto ant = cell->ant();
			auto player = ant->player();

			json["cell"]["type"] = "ant";
			json["cell"]["ant"]["type"] = AntTypeToString(ant->type());
			json["cell"]["ant"]["player"] = player ? player->index() : 0xffffffff;
			json["cell"]["ant"]["health"] = su::String_format2("%.2f", ant->healthPercent());
			json["cell"]["ant"]["satiety"] = su::String_format2("%.2f", ant->satietyPercent());
		}

		file << json << std::endl;
	}

	file.close();
}

};
