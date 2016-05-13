import QtQuick 2.5
import QtQuick.Controls 1.4

TextEdit
{
    FontLoader{ id: loader; source: "fonts/Bitstream-Vera-Sans-Mono/VeraMono.ttf"; }
    FontLoader{ source: "fonts/Bitstream-Vera-Sans-Mono/VeraMono-Bold.ttf"; }
    FontLoader{ source: "fonts/Bitstream-Vera-Sans-Mono/VeraMono-Italic.ttf"; }

    font.family: loader.name;
    font.pixelSize: 11;

    selectByMouse: true
    mouseSelectionMode: TextEdit.SelectCharacters
    selectionColor: "#3d4856"
    color: "#fff"

    textFormat: TextEdit.PlainText
    wrapMode: TextEdit.NoWrap
}
