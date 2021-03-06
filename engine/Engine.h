#ifndef _ENGINE_H
#define _ENGINE_H

#include <QMap>
#include <QSet>
#include <QStringList>
#include <QString>

class Player;
class PlayerListener;
class GameRules;

class Engine : public QObject
{
Q_OBJECT

public:
	enum MoveResult
	{
		ValidMove,
		InvalidMove,
		Timeout
	};
	enum GameResult
	{
		Tie,
		PlayerZeroWon,
		PlayerOneWon,
		Undefined
	};
	Engine(GameRules *rules = NULL);

	Player *loadExternalPlayer(int id);

	bool registerPlayer(Player *player);
	void unregisterPlayer(Player *player);
	void registerPlayerListener(PlayerListener *listener);
	void unregisterPlayerListener(PlayerListener *listener);

	QString getPlayerName(int player);
	bool parseArgs(QStringList args);
	QString getParam(QString name);
	QStringList getParamList(QString name);

protected:
	QStringList getPlayerParams(int id);

private slots:
	void receiveFromPlayer(int id, QString msg, int elapsed);
	void onPlayerLeave(int id);

private:
	void stop(GameResult res);
	void forwardMove(int id, QString move);
	void printStats(GameResult res);
	void sendToPlayer(int id, QString msg);
	int getNextPlayer(int player);

	GameRules *rules;
	QMap<int, Player*> players;
	QSet<PlayerListener*> listeners;
	QMap<QString, QStringList> parameters;
};

#endif
