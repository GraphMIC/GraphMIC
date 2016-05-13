import QtQuick 2.4
import QtQuick.Controls 1.4
import org.graphmic.core.lib 1.0 as Lib

Lib.TextButton
{
  id: button

  property int btnWidth: 35;
  property int btnHeight: 15;
  property string text;
  property ExclusiveGroup exclusiveGroup: null

  label.text: text
  label.width: btnWidth
  label.height: btnHeight
  label.wrapMode: Text.NoWrap
  label.elide: Text.ElideNone
  label.verticalAlignment: Text.AlignVCenter
  toggle: false

    onExclusiveGroupChanged:
    {
        if (exclusiveGroup)
            exclusiveGroup.bindCheckable(button)
    }
}
