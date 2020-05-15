


class NetworkManagerClient : public NetworkManager
{
	enum NetworkClientState
	{
		NCS_Uninitialized,
		NCS_SayingHello,
		NCS_Welcomed,
		NCS_Lobby
	};

public:
	static NetworkManagerClient*	sInstance;

	static	void	StaticInit( const SocketAddress& inServerAddress, const string& inName );

			void	SendOutgoingPackets();

	virtual void	ProcessPacket( InputMemoryBitStream& inInputStream, const SocketAddress& inFromAddress ) override;

			const	WeightedTimedMovingAverage&		GetAvgRoundTripTime()	const	{ return mAvgRoundTripTime; }
			float									GetRoundTripTime()		const	{ return mAvgRoundTripTime.GetValue(); }
			int		GetPlayerId()											const	{ return mPlayerId; }
			string	GetPlayerTeam()											const	{ return mPlayerTeam; }
			float	GetLastMoveProcessedByServerTimestamp()					const	{ return mLastMoveProcessedByServerTimestamp; }
private:
			NetworkManagerClient();
			void Init( const SocketAddress& inServerAddress, const string& inName );

			void	UpdateSayingHello();
			void	SendHelloPacket();

			void	HandleWelcomePacket( InputMemoryBitStream& inInputStream );
			void	HandleStatePacket( InputMemoryBitStream& inInputStream );
			void	ReadLastMoveProcessedOnServerTimestamp( InputMemoryBitStream& inInputStream );

			void	HandleGameObjectState( InputMemoryBitStream& inInputStream );
			void	HandleScoreBoardState( InputMemoryBitStream& inInputStream );

			void	UpdateSendingInputPacket();
			void	SendInputPacket();

			void	UpdateLobbyPacket();

			void	DestroyGameObjectsInMap( const IntToGameObjectMap& inObjectsToDestroy );


	
	DeliveryNotificationManager	mDeliveryNotificationManager;
	ReplicationManagerClient	mReplicationManagerClient;

	SocketAddress		mServerAddress;

	NetworkClientState	mState;

	float				mTimeOfLastHello;
	float				mTimeOfLastInputPacket;

	string				mName;
	int					mPlayerId;
	string				mPlayerTeam;

	float				mLastMoveProcessedByServerTimestamp;

	WeightedTimedMovingAverage	mAvgRoundTripTime;
	float						mLastRoundTripTime;

};