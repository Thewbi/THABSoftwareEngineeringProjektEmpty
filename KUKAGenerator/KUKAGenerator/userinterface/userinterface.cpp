#include "Userinterface.h"



namespace kuka_generator
{
    // this constructor places the process_context into the member variable called
    // process_context_ via the so-called initializer list. The initializer list are
    // all the statements after the colon.
    //
    // process_context_(process_context) means that process_context_ is set to the procese_context parameter.
    Userinterface::Userinterface(kuka_generator::ProcessContext& process_context) : process_context_(process_context)
    {
        // empty
    }

    int Userinterface::process()
    {
        // declaring variables
        int i = 0;
        int j = 0;

        // communicate with user
        std::cout << "******************************************************************************************************************************" << std::endl;
        std::cout << "[Userinterface] start processing!" << std::endl;
        std::cout << "[Userinterface] Willkommen!" << std::endl;
        std::cout << "[Userinterface] Dieses Programm wurde erstellt von: Janek Berlin, Thong Phi, Wolfgang Bischoff, Marcel Dudek, Tom Bischof" << std::endl;
        std::cout << "[Userinterface] Bitte den Dateipfad [Datei!] angegeben, unter welchem die einzulesenden Daten abgelegt sind!" << std::endl;

        // get user input
        std::getline(std::cin, user_input_file);

        // communicate with user
        std::cout << "[Userinterface] Es wurde folgendes eingegeben: '" << user_input_file << "'" << std::endl;
        std::cout << "[Userinterface] Starte Pruefung der Eingabe..." << std::endl;

        // check if userinput is empty
        while (checkinput(user_input_file) == 0)
        {
            std::cout << "[Userinterface] Es wurde nichts eingegeben!" << std::endl;
            std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
            std::getline(std::cin, user_input_file);
        };

        // check if userinput is a valid path
        while (checkpath(user_input_file) == 0)
        {
            std::cout << "[Userinterface] Der Eingabewert '" << user_input_file << "' ist kein gueltiger Dateipfad!" << std::endl;
            user_input_file.clear();
            std::cout << "[Userinterface] Bitte den Dateipfad [Datei!] angegeben, unter welchem die einzulesenden Daten abgelegt sind!" << std::endl;
            std::getline(std::cin, user_input_file);
        };

        // set variable
        process_context_.input_file = user_input_file;

        // communicate with user
        std::cout << "[Userinterface] Die Eingabe des Inputpfads war erfolgreich!" << std::endl << std::endl;
        std::cout << "[Userinterface] Bitte den Dateipfad [Verzeichnis!] angegeben, unter welchem die generierte Datei abgelegt werden soll!" << std::endl;

        // get user input
        std::getline(std::cin, user_output_file);

        // communicate with user
        std::cout << "[Userinterface] Es wurde folgendes eingegeben: '" << user_output_file << "'" << std::endl;
        std::cout << "[Userinterface] Starte Pruefung der Eingabe..." << std::endl;

        // check if userinput is empty
        while (checkinput(user_output_file) == 0)
        {
            std::cout << "[Userinterface] Es wurde nichts eingegeben!" << std::endl;
            std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
            std::getline(std::cin, user_output_file);
        };

        // check if userinput is a valid path
        while (checkpath(user_output_file) == 0)
        {
            std::cout << "[Userinterface] Der Eingabewert '" << user_output_file << "' ist kein gueltiger Dateipfad!" << std::endl;
            user_output_file.clear();
            std::cout << "[Userinterface] Bitte den Dateipfad [Verzeichnis!] angegeben, unter welchem die generierte Datei abgelegt werden soll!" << std::endl;
            std::getline(std::cin, user_output_file);
        };

        // set variable
        process_context_.output_file = user_output_file;

        // communicate with user
        std::cout << "[Userinterface] Die Eingabe des Outputpfads war erfolgreich!" << std::endl << std::endl;
        std::cout << "[Userinterface] Soll die voreingestellte Orientierung uebernommen werden, oder die Orientierung selbst definiert werden?" << std::endl;
        std::cout << "[Userinterface] y = Orientierung uebernehmen!" << std::endl;
        std::cout << "[Userinterface] n = Orientierung selbst angeben!" << std::endl;
        std::getline(std::cin, user_defined_oriantation_mode);

        // check userselection
        while (user_defined_oriantation_mode != "y" and user_defined_oriantation_mode != "Y" and user_defined_oriantation_mode != "n" and user_defined_oriantation_mode != "N")
        {
            // system("cls"); // clear consol?
            std::cout << "[Userinterface] Der Eingabewert '" << user_defined_oriantation_mode << "' entspricht keiner der gegebenen Moeglichkeiten!" << std::endl;
            user_defined_oriantation_mode.clear();
            std::cout << "[Userinterface] Soll die voreingestellte Orientierung uebernommen werden, oder die Orientierung selbst definiert werden?" << std::endl;
            std::cout << "[Userinterface] y = Orientierung uebernehmen!" << std::endl;
            std::cout << "[Userinterface] n = Orientierung selbst angeben!" << std::endl;
            std::getline(std::cin, user_defined_oriantation_mode);
        };

        // user selection is either y or n
        if (user_defined_oriantation_mode == "y" or user_defined_oriantation_mode == "Y")
        {
            std::cout << "[Userinterface] Danke fuer die Y Auswahl, die Orientierung der Eingabedatei wird verwendet!" << std::endl;
            process_context_.use_user_defined_orientation = { false }; // set variable
        }
        else if (user_defined_oriantation_mode == "n" or user_defined_oriantation_mode == "N")
        {
            std::cout << "[Userinterface] Danke fuer die N Auswahl" << std::endl;
            std::cout << "[Userinterface] Die Eingabe der Orientierung erfordert das definieren einer neunwertigen Matrix!" << std::endl;
            std::cout << "[Userinterface] Die Werte muessen einzeln, nacheinander eingegeben werden!" << std::endl;
            std::cout << "[Userinterface] Jeder Wert ist durch seine Zeilenummer / Spaltennummer addressiert!" << std::endl;
            std::cout << "[Userinterface] Nachfolgend der schematische Aufbau der Matrix:" << std::endl;
            std::cout << "[Userinterface] Maxtix(3x3):" << std::endl << std::endl;
            std::cout << "[Userinterface] \t\t Spalte \t Spalte \t Spalte" << std::endl << std::endl;
            std::cout << "[Userinterface] Zeile \t\t    [ ]   \t   [ ]  \t   [ ]  " << std::endl;
            std::cout << "[Userinterface] Zeile \t\t    [ ]   \t   [ ]  \t   [ ]  " << std::endl;
            std::cout << "[Userinterface] Zeile \t\t    [ ]   \t   [ ]  \t   [ ]  " << std::endl;


            for (i = 1; i <= 3; i++) // loop through rows
            {
                for (j = 1; j <= 3; j++) // loop through columns
                {
                    std::cout << "[Userinterface] Bitte den Wert fuer Position [" << i << "," << j << "] angeben!" << std::endl;
                    std::getline(std::cin, user_defined_orientation);

                        // check if userinput is empty
                        while (checkinput(user_defined_orientation) == 0)
                        {
                            std::cout << "[Userinterface] Es wurde nichts eingegeben!" << std::endl;
                            std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
                            std::getline(std::cin, user_defined_orientation);
                        };

                    // check if userinput is int or double
                    while (checkdouble(user_defined_orientation) == 0)
                    {
                        std::cout << "[Userinterface] Es wurde keine Zahl eingegeben!" << std::endl;
                        std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
                        std::getline(std::cin, user_defined_orientation);
                    };

                    process_context_.user_defined_orientation[i * j] = std::stod(user_defined_orientation);
                    user_defined_orientation = ""; // reset variable
                };
            };

            process_context_.use_user_defined_orientation = { true }; // set variable
        };

        // communicate with user
        std::cout << "[Userinterface] Die Eingabe der Orientierung war erfolgreich!" << std::endl << std::endl;
        std::cout << "[Userinterface] Soll die voreingestellte Geschwindigkeit uebernommen werden, oder die Geschwindigkeit selbst definiert werden?" << std::endl;
        std::cout << "[Userinterface] y = Geschwindigkeit uebernehmen!" << std::endl;
        std::cout << "[Userinterface] n = Geschwindigkeit selbst angeben!" << std::endl;
        std::getline(std::cin, user_defined_velocity_mode);

        // check userselection
        while (user_defined_velocity_mode != "y" and user_defined_velocity_mode != "Y" and user_defined_velocity_mode != "n" and user_defined_velocity_mode != "N")
        {
            // system("cls"); // clear consol?
            std::cout << "[Userinterface] Der Eingabewert '" << user_defined_velocity_mode << "'entspricht keiner der gegebenen Moeglichkeiten!" << std::endl;
            user_defined_velocity_mode.clear();
            std::cout << "[Userinterface] Soll die voreingestellte Geschwindigkeit uebernommen werden, oder die Geschwindigkeit selbst definiert werden?" << std::endl;
            std::cout << "[Userinterface] y = Geschwindigkeit uebernehmen!" << std::endl;
            std::cout << "[Userinterface] n = Geschwindigkeit selbst angeben!" << std::endl;
            std::getline(std::cin, user_defined_velocity_mode);
        };

        // user selection is either y or n
        if (user_defined_velocity_mode == "y" or user_defined_velocity_mode == "Y")
        {
            std::cout << "[Userinterface] Danke fuer die Y Auswahl, die Geschwindigkeit der Eingabedatei wird verwendet!" << std::endl;
            process_context_.use_user_defined_velocity = { false }; // set variable
        }
        else if (user_defined_velocity_mode == "n" or user_defined_velocity_mode == "N")
        {
            std::cout << "[Userinterface] Danke fuer die N Auswahl" << std::endl;
            std::cout << "[Userinterface] Welche Geschwindigkeit soll benutzt werden?" << std::endl;
            std::getline(std::cin, user_defined_velocity);

            // check if userinput is empty
            while (checkinput(user_defined_velocity) == 0)
            {
                std::cout << "[Userinterface] Es wurde nichts eingegeben!" << std::endl;
                std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
                std::getline(std::cin, user_defined_velocity);
            };

            // check if userinput is int or double
            while (checkdouble(user_defined_velocity) == 0)
            {
                std::cout << "[Userinterface] Es wurde keine Zahl eingegeben!" << std::endl;
                std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
                std::getline(std::cin, user_defined_velocity);
            };
            process_context_.use_user_defined_velocity = { true }; // set variable
            process_context_.user_defined_velocity = std::stod(user_defined_velocity); // set variable
        };

        // communicate with user
        std::cout << "[Userinterface] Die Eingabe der Geschwindigkeit war erfolgreich!" << std::endl << std::endl;
        std::cout << "[Userinterface] Bitte die Filterlaenge [Ganzzahl!] fuer die Datenfilterung angeben!" << std::endl;
        std::getline(std::cin, user_defined_filter_orientation);

        // check if userinput is empty
        while (checkinput(user_defined_filter_orientation) == 0)
        {
            std::cout << "[Userinterface] Es wurde nichts eingegeben!" << std::endl;
            std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
            std::getline(std::cin, user_defined_filter_orientation);
        };

        // check if userinput is int
        while (checkint(user_defined_filter_orientation) == 0)
        {
            std::cout << "[Userinterface] Es wurde keine Ganzzahl eingegeben!" << std::endl;
            std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
            std::getline(std::cin, user_defined_filter_orientation);
        };
        process_context_.length_filter_orientation = std::stoi(user_defined_filter_orientation); // set variable

        // communicate with user
        std::cout << "[Userinterface] Die Eingabe der Filterlaenge war erfolgreich!" << std::endl << std::endl;
        std::cout << "[Userinterface] Bitte die Filterlaenge [Ganzzahl!] fuer die Aproximation angeben!" << std::endl;
        std::getline(std::cin, user_defined_filter_position);

        // check if userinput is empty
        while (checkinput(user_defined_filter_position) == 0)
        {
            std::cout << "[Userinterface] Es wurde nichts eingegeben!" << std::endl;
            std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
            std::getline(std::cin, user_defined_filter_position);
        };

        // check if userinput is int
        while (checkint(user_defined_filter_position) == 0)
        {
            std::cout << "[Userinterface] Es wurde keine Ganzzahl eingegeben!" << std::endl;
            std::cout << "[Userinterface] Bitte die Eingabe wiederholen!" << std::endl;
            std::getline(std::cin, user_defined_filter_position);
        };
        process_context_.length_filter_position = std::stoi(user_defined_filter_position); // set variable

        std::cout << "[Userinterface] Die Eingabe der Filterlaenge war erfolgreich!" << std::endl << std::endl;
        std::cout << "[Userinterface] done!" << std::endl;
        std::cout << "******************************************************************************************************************************" << std::endl;

        return NO_ERROR;
    };

    int Userinterface::checkinput(std::string& user_input)
    {
        if (user_input.empty())
        {
            return 0;
        }
        return 1;
    };

    int Userinterface::checkpath(std::string& user_input)
    {
        DWORD fileAttributes = GetFileAttributesA(user_input.c_str());
        if (fileAttributes == INVALID_FILE_ATTRIBUTES)
        {
            return 0;
        }
        return 1;
    };

    int Userinterface::checkint(std::string& user_input)
    {
        std::cout << "[Userinterface] Eingabewert: " << user_input << std::endl;
        std::istringstream iss(user_input);
        int inputasint = 0;
        char inputaschar = '\0';
        return iss >> inputasint && !(iss >> inputaschar); // returns 1 if successfull, else 0
    };

    int Userinterface::checkdouble(std::string& user_input)
    {
        std::cout << "[Userinterface] Eingabewert: " << user_input << std::endl;
        std::istringstream iss(user_input);
        double inputasdouble = 0.0;
        char inputaschar = '\0';
        return iss >> inputasdouble && !(iss >> inputaschar); // returns 1 if successfull, else 0
    };
}
