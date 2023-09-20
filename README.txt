
TODO:
    - Fix issue with ultimate skill JSON not being packages with compilation. This issues causes game to not work if compiling is done to different
    directory
    - Make execution open a new terminal of a set size so visuals are rendered properly instead of partial rendering if terminal is too small
    - improve rendering pipeline to enable resizing of terminal window



RPGBattle is a classically inspired text-based RPG battle game.

This program requires:
    C++ 20
    Curses
    Boost

Let $TOP_DIR denote the directory containing this README file.
Let $INSTALL_DIR denote the directory which this software is to be installed.
Let $SAVE_FILE_PATH denote the path to user created custom game save file.

Build and installation commands:
    cd $TOP_DIR
    cmake -H. -Btmp -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
    cmake --build tmp --clean-first --target install

To Launch demo game use the command:
    $INSTALL_DIR/bin/demo

To Launch game using default save file use the command:
    $INSTALL_DIR/bin/RPGBattle

To Launch game using user created save file use the command:
    $INSTALL_DIR/bin/RPGBattle $SAVE_FILE_PATH

Additional user defined JSON save file template (Alterations to below JSON template are at users risk for undefined behavior):
{
    "Saves": [
        {
            "Name": "",
            "Level": "0",
            "Exp": "0",
            "Exp_needed": "0",
            "Skill_id": "0",
            "Attribute Points": "0",
            "Strength": "0",
            "Defense": "0",
            "Dexterity": "0",
            "Intelligence": "0",
            "Save_DateTime": "0"
        },
        {
            "Name": "",
            "Level": "0",
            "Exp": "0",
            "Exp_needed": "0",
            "Skill_id": "0",
            "Attribute Points": "0",
            "Strength": "0",
            "Defense": "0",
            "Dexterity": "0",
            "Intelligence": "0",
            "Save_DateTime": "0"
        },
        {
            "Name": "",
            "Level": "0",
            "Exp": "0",
            "Exp_needed": "0",
            "Skill_id": "0",
            "Attribute Points": "0",
            "Strength": "0",
            "Defense": "0",
            "Dexterity": "0",
            "Intelligence": "0",
            "Save_DateTime": "0"
        }
    ]
}
