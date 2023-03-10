# Файл написан на языке C 

void main()

{

	//Настройка погоды при запуске
	//INIT WEATHER BEFORE ECONOMY INIT------------------------

	Weather weather = g_Game.GetWeather();



	weather.MissionWeather(false);    // false = use weather controller from Weather.c



	weather.GetOvercast().Set( Math.RandomFloatInclusive(0.4, 0.6), 1, 0);

	weather.GetRain().Set( 0, 0, 1);

	weather.GetFog().Set( Math.RandomFloatInclusive(0.05, 0.1), 1, 0);



	//INIT ECONOMY--------------------------------------

	Hive ce = CreateHive();

	if ( ce )

		ce.InitOffline();


	//Настройка даты при запуске
	//DATE RESET AFTER ECONOMY INIT-------------------------

	int year, month, day, hour, minute;

	int reset_month = 9, reset_day = 20;

	GetGame().GetWorld().GetDate(year, month, day, hour, minute);



	if ((month == reset_month) && (day < reset_day))

	{

		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);

	}

	else

	{

		if ((month == reset_month + 1) && (day > reset_day))

		{

			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);

		}

		else

		{

			if ((month < reset_month) || (month > reset_month + 1))

			{

				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);

			}

		}

	}

}



//Настройка спавна
class CustomMission: MissionServer

{

	//Настройка количества хп при спавне
	void SetRandomHealth(EntityAI itemEnt)

	{

		if ( itemEnt )

		{

			//хп рандомно от 0.45 до 0.65
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );

			itemEnt.SetHealth01( "", "", rndHlt );

		}

	}



	//Спавн игрока
	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)

	{

		Entity playerEnt;

		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );

		Class.CastTo( m_player, playerEnt );



		GetGame().SelectPlayer( identity, m_player );



		return m_player;

	}



	//Настройка стартового лута
	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)

	{

		EntityAI itemClothing;

		EntityAI itemEnt;

		ItemBase itemBs;

		float rand;



		itemClothing = player.FindAttachmentBySlotName( "Body" );

		if ( itemClothing )

		{

			SetRandomHealth( itemClothing );

			

			itemEnt = itemClothing.GetInventory().CreateInInventory( "Rag" ); //Rag это класснейм предмета (ткани)

			if ( Class.CastTo( itemBs, itemEnt ) )

				itemBs.SetQuantity( 4 );//Количество



			SetRandomHealth( itemEnt );



			string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };

			int rndIndex = Math.RandomInt( 0, 4 );

			itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );

			SetRandomHealth( itemEnt );



			rand = Math.RandomFloatInclusive( 0.0, 1.0 );

			if ( rand < 0.35 )

				itemEnt = player.GetInventory().CreateInInventory( "Apple" );

			else if ( rand > 0.65 )

				itemEnt = player.GetInventory().CreateInInventory( "Pear" );

			else

				itemEnt = player.GetInventory().CreateInInventory( "Plum" );



			SetRandomHealth( itemEnt );

		}

		

		itemClothing = player.FindAttachmentBySlotName( "Legs" );

		if ( itemClothing )

			SetRandomHealth( itemClothing );

		

		itemClothing = player.FindAttachmentBySlotName( "Feet" );

	}

};



Mission CreateCustomMission(string path)

{

	return new CustomMission();

}
