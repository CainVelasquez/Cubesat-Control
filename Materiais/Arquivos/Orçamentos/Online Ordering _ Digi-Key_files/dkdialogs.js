function dlgHelp(res) {
    var url = "/classic/dialog/help.aspx?id=" + encodeURIComponent(res);
    var btns = {};

    $.get(url, function (data, status) {
        var dlg=$(data);

        btns[dlg.attr("close")] = function () { $(this).dialog("close"); };

        dlg.dialog({
            resizable: false,
            modal: true,
            closeOnEscape: true,
            close: function (e) { $(this).dialog('destroy').remove(); },
            buttons: btns
        });
    });
}
