	/* /// Combine locations files
	char country[100];
	char state[100];
	char city[100];
	int latd; // latitude degrees
	int latm; // latitude minutes
	int lond; // longitude degrees
	int lonm; // longitude minutes
	char ns;
	char ew;

	ofstream outfile( "data\\locations.dat" );
	if( !outfile.is_open() )
	{
		CSDebug( "Error opening output file", "CDataStarf::LoadLocations" );
		exit(0);
		return;
	}

	// USA

	country = CString("USA");

	ifstream usa( "data\\usa.dat" );
	if( !usa.is_open() )
	{
		CSDebug( "Error opening input file", "CDataStarf::LoadLocations" );
		exit(0);
		return;
	}

	// State loop
	while( TRUE )
	{
		usa.seekg( 7, ios::cur );
		if( usa.peek() == ' ' )
		{
			usa.get(); // ' '

			// Read city and its lat and long
			usa.read( city, 26 );
			usa >> latd;
			usa.get(); // '°'
			usa.get(); // ' '
			usa >> latm;
			usa.get(); //'
			usa.get(); // 
			ns = usa.get(); // N/S
			usa >> lond;
			usa.get(); // '°'
			usa.get(); // ' '
			usa >> lonm;
			usa.get(); //'
			usa.get(); // 
			ew = usa.get(); // E/W
			usa.get(); // '\n'

			outfile << country << ", " << state << ", " << city << latd << ' ' << latm << ns << "  " << lond << ' ' << lonm << ew << endl;
		}
		else if( usa.peek() != EOF )
		{
			// Read state
			usa.getline( state, 100 );
		}
		else
			break;
	}

	usa.close();

	// Canada

	country = CString("CANADA");

	ifstream canada( "data\\canada.dat" );
	if( !canada.is_open() )
	{
		CSDebug( "Error opening input file", "CDataStarf::LoadLocations" );
		exit(0);
		return;
	}

	// State loop
	while( TRUE )
	{
		canada.seekg( 7, ios::cur );
		if( canada.peek() == ' ' )
		{
			canada.get(); // ' '

			// Read city and its lat and long
			canada.read( city, 26 );
			canada >> latd;
			canada.get(); // '°'
			canada.get(); // ' '
			canada >> latm;
			canada.get(); //'
			canada.get(); // 
			ns = canada.get(); // N/S
			canada >> lond;
			canada.get(); // '°'
			canada.get(); // ' '
			canada >> lonm;
			canada.get(); //'
			canada.get(); // 
			ew = canada.get(); // E/W
			canada.get(); // '\n'

			outfile << country << ", " << state << ", " << city << latd << ' ' << latm << ns << "  " << lond << ' ' << lonm << ew << endl;
		}
		else if( canada.peek() != EOF )
		{
			// Read state
			canada.getline( state, 100 );
		}
		else
			break;
	}

	canada.close();

	// Other countries

	ifstream other( "data\\other.dat" );
	if( !other.is_open() )
	{
		CSDebug( "Error opening input file", "CDataStarf::LoadLocations" );
		exit(0);
		return;
	}

	// State loop
	while( TRUE )
	{
		other.seekg( 7, ios::cur );
		int p = other.tellg();
		c = other.peek();
		if( other.peek() == ' ' )
		{
			other.get(); // ' '

			// Read city and its lat and long
			other.read( city, 26 );
			other >> latd;
			other.get(); // '°'
			other.get(); // ' '
			other >> latm;
			other.get(); //'
			other.get(); // 
			ns = other.get(); // N/S
			other >> lond;
			other.get(); // '°'
			other.get(); // ' '
			other >> lonm;
			other.get(); //'
			other.get(); // 
			ew = other.get(); // E/W
			other.get(); // '\n'

			outfile << state << ", " << city << latd << ' ' << latm << ns << "  " << lond << ' ' << lonm << ew << endl;
		}
		else if( other.peek() != EOF )
		{
			p = other.tellg();
			// Read country
			other.getline( state, 100 );
			p = other.tellg();
			c = other.peek();
		}
		else
			break;
	}

	other.close();

	outfile.close();
	*/
