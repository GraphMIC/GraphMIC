import QtQuick 2.4
import QtQuick.Controls 1.4
import org.graphmic.core.lib 1.0 as Lib

Lib.TextButton
{
  id: button

  property var toolItem;
  property int btnWidth: 40;
  property int btnHeight: 15;
  property string text;
  property ExclusiveGroup exclusiveGroup: null

  label.text: text
  label.width: btnWidth
  label.height: btnHeight
  label.wrapMode: Text.WordWrap
  label.elide: Text.ElideRight
  toggle: true

  onCheckedChanged: checked ? toolItem.activateTool(label.text) : toolItem.deactivateTool(label.text);
    onExclusiveGroupChanged:
    {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(button)
    }
}
