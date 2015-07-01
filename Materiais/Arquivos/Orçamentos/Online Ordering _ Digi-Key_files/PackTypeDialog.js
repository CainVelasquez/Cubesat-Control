    function enable(rbID) {
        if (document.getElementById(rbID) != null) {
            document.getElementById(rbID).disabled = false;
            document.getElementById(rbID).label.style.color = 'black';
            document.getElementById(rbID).label.innerHTML =
                document.getElementById(rbID).label.innerHTML.replace('<font color=\"lightgray\">', '<font color=\"red\">');
            document.getElementById(rbID).label.innerHTML =
                document.getElementById(rbID).label.innerHTML.replace('<font color=\"lightgray\">', '<font color=\"red\">');
            var reelFeeLabels = document.getElementsByName('lblReelFee');
            for (var x = 0; x < reelFeeLabels.length; x++) {
                reelFeeLabels[x].style.color = 'black';
            }
            if (document.getElementById('lblUnitPrice_' + rbID) != null) {
                document.getElementById('lblUnitPrice_' + rbID).style.color = 'black';
            }
            if (document.getElementById('lblExtPrice_' + rbID) != null) {
                document.getElementById('lblExtPrice_' + rbID).style.color = 'black';
            }
            if (document.getElementById('lblSubtotal_' + rbID) != null) {
                document.getElementById('lblSubtotal_' + rbID).style.color = 'black';
                document.getElementById('lblSubtotal_' + rbID).innerHTML = document.getElementById('lblSubtotal_' + rbID).innerHTML.replace('lightgray', 'green');
            }
            if (document.getElementById('lblYouSave_' + rbID) != null) {
                document.getElementById('lblYouSave_' + rbID).style.color = 'black';
                document.getElementById('lblYouSave_' + rbID).innerHTML = document.getElementById('lblYouSave_' + rbID).innerHTML.replace('lightgray', 'green');
            }

            $(".green").css('color', 'green');
            $(".border_top_save").css("border-top", "1px solid black");
            $(".border_bottom_save").css("border-bottom", "1px solid black");
        }
    }

function disable(rbID) {
    if (document.getElementById(rbID) != null) {
        document.getElementById(rbID).disabled = true;
        document.getElementById(rbID).label.style.color = 'lightgray';
        document.getElementById(rbID).label.innerHTML =
            document.getElementById(rbID).label.innerHTML.replace('<font color=\"red\">', '<font color=\"lightgray\">');
        document.getElementById(rbID).label.innerHTML =
            document.getElementById(rbID).label.innerHTML.replace('<font color=\"red\">', '<font color=\"lightgray\">');
        var reelFeeLabels = document.getElementsByName('lblReelFee');
        for (var x = 0; x < reelFeeLabels.length; x++) {
            reelFeeLabels[x].style.color = 'lightgray';
        }
        if (document.getElementById('lblUnitPrice_' + rbID) != null) {
            document.getElementById('lblUnitPrice_' + rbID).style.color = 'lightgray';
        }
        if (document.getElementById('lblExtPrice_' + rbID) != null) {
            document.getElementById('lblExtPrice_' + rbID).style.color = 'lightgray';
        }
        if (document.getElementById('lblSubtotal_' + rbID) != null) {
            document.getElementById('lblSubtotal_' + rbID).style.color = 'lightgray';
            document.getElementById('lblSubtotal_' + rbID).innerHTML = document.getElementById('lblSubtotal_' + rbID).innerHTML.replace('green', 'lightgray');
        }
        if (document.getElementById('lblYouSave_' + rbID) != null) {
            document.getElementById('lblYouSave_' + rbID).style.color = 'lightgray';
            document.getElementById('lblYouSave_' + rbID).innerHTML = document.getElementById('lblYouSave_' + rbID).innerHTML.replace('green', 'lightgray');
        }

        $(".border_top_save").css("border-top", "1px solid lightgray");
        $(".border_bottom_save").css("border-bottom", "1px solid lightgray");
    }
}

function fixFieldsGroup1() {
    var labels = document.getElementsByTagName('LABEL');
    for (var i = 0; i < labels.length; i++) {
        if (labels[i].htmlFor != '') {
            var elem = document.getElementById(labels[i].htmlFor);
            if (elem)
                elem.label = labels[i];
        }
    }
    if (document.getElementById('rb1') != null && document.getElementById('rb1').checked) {
        $('[id^=hf_rb]').val('false');
        $('#hf_rb1_selected').val('true');
        if ((document.getElementById('hf_rb1a_selected') != null) && (document.getElementById('hf_rb1b_selected') != null)) {
            if (document.getElementById('rb1a').checked) {
                $('#hf_rb1a_selected').val('true');
            }
            else if (document.getElementById('rb1b').checked) {
                $('#hf_rb1b_selected').val('true');
            }
        }
        if (document.getElementById('lblAndYourChoice') != null) {
            document.getElementById('lblAndYourChoice').style.color = 'black';
        }
        enable('rb1a');
        enable('rb1b');
        if (document.getElementById('lblLowerPrice') != null) {
            document.getElementById('lblLowerPrice').style.color = 'black';
        }
        enable('rb1c');
        enable('rb1d');
    }
    else if (document.getElementById('rb2') != null && document.getElementById('rb2').checked) {
        $('[id^=hf_rb]').val('false');
        $('#hf_rb2_selected').val('true');
        if (document.getElementById('lblAndYourChoice') != null) {
            document.getElementById('lblAndYourChoice').style.color = 'lightgray';
        }

        disable('rb1a');
        disable('rb1b');
        if (document.getElementById('lblLowerPrice') != null) {
            document.getElementById('lblLowerPrice').style.color = 'lightgray';
        }
        disable('rb1c');
        disable('rb1d');
    }
    else if (document.getElementById('rb3') != null && document.getElementById('rb3').checked) {
        $('[id^=hf_rb]').val('false');
        $('#hf_rb3_selected').val('true');
        if (document.getElementById('lblAndYourChoice') != null) {
            document.getElementById('lblAndYourChoice').style.color = 'lightgray';
        }

        disable('rb1a');
        disable('rb1b');
        if (document.getElementById('lblLowerPrice') != null) {
            document.getElementById('lblLowerPrice').style.color = 'lightgray';
        }
        disable('rb1c');
        disable('rb1d');
    }
    if (document.getElementById('rbDel') != null && document.getElementById('rbDel').checked) {
        $('[id^=hf_rb]').val('false');
        if (document.getElementById('lblAndYourChoice') != null) {
            document.getElementById('lblAndYourChoice').style.color = 'lightgray';
        }
        disable('rb1a');
        disable('rb1b');
        if (document.getElementById('lblLowerPrice') != null) {
            document.getElementById('lblLowerPrice').style.color = 'lightgray';
        }
        disable('rb1c');
        disable('rb1d');
        if (document.getElementById('btnDeleteFastAdd') != null) {
            document.getElementById('btnDeleteFastAdd').removeAttribute('disabled');
        }
        var attribute = document.createAttribute("disabled");
        attribute.nodeValue = "disabled";
        if (document.getElementById('btnCancelFastAdd') != null) {
            document.getElementById('btnCancelFastAdd').setAttributeNode(attribute);
        }
        var attribute2 = document.createAttribute("disabled");
        attribute2.nodeValue = "disabled";
        if (document.getElementById('btnAddFastAdd') != null) {
            document.getElementById('btnAddFastAdd').setAttributeNode(attribute2);
        }
    }
    else if (document.getElementById('rbDel') != null && document.getElementById('rbDel').checked == false) {
        if (document.getElementById('btnAddFastAdd') != null) {
            document.getElementById('btnAddFastAdd').removeAttribute('disabled', 0);
        }
        if (document.getElementById('btnCancelFastAdd') != null) {
            document.getElementById('btnCancelFastAdd').removeAttribute('disabled', 0);
        }
        var attribute = document.createAttribute("disabled");
        attribute.nodeValue = "disabled"
        if (document.getElementById('btnDeleteFastAdd') != null) {
            document.getElementById('btnDeleteFastAdd').setAttributeNode(attribute);
        }
    }
}

function fixFieldsGroup2() {
    if ((document.getElementById('rb1a') != null) && (document.getElementById('rb1a').checked)) {
        $("#hf_rb1a_selected").val("true");
        $("#hf_rb1b_selected").val("false");
        $("#hf_rb1c_selected").val("false");
        $("#hf_rb1d_selected").val("false");
    }
    else if ((document.getElementById('rb1b') != null) && (document.getElementById('rb1b').checked)) {
        $("#hf_rb1a_selected").val("false");
        $("#hf_rb1b_selected").val("true");
        $("#hf_rb1c_selected").val("false");
        $("#hf_rb1d_selected").val("false");
    }
    else if ((document.getElementById('rb1c') != null) && (document.getElementById('rb1c').checked)) {
        $("#hf_rb1a_selected").val("false");
        $("#hf_rb1b_selected").val("false");
        $("#hf_rb1c_selected").val("true");
        $("#hf_rb1d_selected").val("false");
    }
    else if ((document.getElementById('rb1d') != null) && (document.getElementById('rb1d').checked)) {
        $("#hf_rb1a_selected").val("false");
        $("#hf_rb1b_selected").val("false");
        $("#hf_rb1c_selected").val("false");
        $("#hf_rb1d_selected").val("true");
    }
}

function complete() {
    /* the following line didn't work in IE, so i'm using the next line instead */
    /*var row = document.getElementsByName('gvAddPartError')[0].rows[document.getElementById('hdnFixingErrorIndex').value];*/
    var row = getElementsByName_iefix('table', 'gvAddPartError')[0].rows[document.getElementById('hdnFixingErrorIndex').value];
    row.cells[1].children[0].value = "";
    row.cells[2].children[0].value = "";
    row.cells[3].children[0].value = "";
    WebForm_DoPostBackWithOptions(new WebForm_PostBackOptions("ctl00$ctl00$mainContentPlaceHolder$mainContentPlaceHolder$btnAddListToOrderError", "", true, "", "", false, true));
}

function removeAllErrors() {
    /* the following line didn't work in IE, so i'm using the next line instead */
    /*var row = document.getElementsByName('gvAddPartError')[0].rows[document.getElementById('hdnFixingErrorIndex').value];*/
    var row = getElementsByName_iefix('table', 'gvAddPartError')[0].rows;
    for (i = 1; i < row.length; i++) {
        if (row[i].cells[4].childNodes[3].value == "False") {
            row[i].cells[1].children[0].value = "";
            row[i].cells[2].children[0].value = "";
            row[i].cells[3].children[0].value = "";
        }
    }
    WebForm_DoPostBackWithOptions(new WebForm_PostBackOptions("ctl00$ctl00$mainContentPlaceHolder$mainContentPlaceHolder$btnAddListToOrderError", "", true, "", "", false, true));
}

function cancelFastAdd() {
    $("#form1").dialog("destroy").remove();
}

function deleteFastAdd() {
    complete();
}

function getElementsByName_iefix(tag, name) {
    var elem = document.getElementsByTagName(tag);
    var arr = new Array();
    for (i = 0, iarr = 0; i < elem.length; i++) {
        att = elem[i].getAttribute("name");
        if (att == name) {
            arr[iarr] = elem[i]; iarr++;
        }
    }
    return arr;
}

function doAnalyticsPageLoad() {
    var meta = ["WT.z_page_type", "SC", "WT.z_page_sub_type", "CO", "WT.z_page_id", "RC", "WT.cg_n", "Shopping Cart", "WT.cg_s", "Digi-Key Recommendations Popup"];
    var meta2 = ["WT.tx_u", "#QTY#", "WT.z_offer_type", "#OFFERTYPE#", "WT.pn_sku", "#SKU#", "WT.z_part_id", "#PARTID#", "WT.z_has_extended_price_savings", "#HASEXT#", "WT.z_has_unit_price_savings", "#HASUNIT#", "WT.z_amt_extended_price_savings", "#SAVINGS#", "WT.z_dialog_type", "#DIALOGTYPE#", "WT.z_num_choices", "#NUMCHOICES#" ];

    meta2 = doAnalyticsPageLoadForRadioButton('rb1', meta2);
    meta2 = doAnalyticsPageLoadForRadioButton('rb1a', meta2);
    meta2 = doAnalyticsPageLoadForRadioButton('rb1b', meta2);
    meta2 = doAnalyticsPageLoadForRadioButton('rb1c', meta2);
    meta2 = doAnalyticsPageLoadForRadioButton('rb1d', meta2);
    meta2 = doAnalyticsPageLoadForRadioButton('rb2', meta2);
    meta2 = doAnalyticsPageLoadForRadioButton('rb3', meta2);

    for (var i = 0; i < meta2.length; i++){
        meta2[i] = meta2[i].replace('|#SKU#', '')
                .replace(';#PARTID#', '')
                .replace(';#OFFERTYPE#', '')
                .replace(';#HASEXT#', '')
                .replace(';#HASUNIT#', '')
                .replace(';#SAVINGS#', '')
                .replace(';#QTY#', '');
    }

    var numChoices = $('[id^=rb][id != "rbDel"]').length;

    var dialogType = "";
    if ((meta2[3].indexOf('Upsell') > -1) && (meta2[3].indexOf('Unavail') > -1)){
        dialogType = 'Quantity Unavailable in Selected Packaging (';
    }
    else if ((meta2[3].indexOf('Upsell') > -1)) {
        dialogType = 'Value Calculator (';
    }
    else if ((meta2[3].indexOf('Unavail') > -1)) {
        dialogType = 'Quantity Unavailable in Selected Packaging (';
    }
    dialogType += numChoices + ' Options)';

    meta2[15] = meta2[15].replace('#DIALOGTYPE#', dialogType);
    meta2[17] = meta2[17].replace('#NUMCHOICES#', numChoices);

    var combined = meta.concat(meta2);
    dcsMultiTrack.apply(this, combined);
}

function doAnalyticsPageLoadForRadioButton(rbId, wtMeta) {
    if ($('#' + rbId)[0] != null) {
        for (var i = 0; i < wtMeta.length; i++) {
            wtMeta[i] = wtMeta[i].replace('#OFFERTYPE#', $('#hdn_' + rbId + '_offerType')[0].value + ';#OFFERTYPE#');
            wtMeta[i] = wtMeta[i].replace('#SKU#', $('#hdn_' + rbId + '_partWT')[0].value + '|#SKU#');
            wtMeta[i] = wtMeta[i].replace('#PARTID#', $('#hdn_' + rbId + '_partIdWT')[0].value + ';#PARTID#');
            wtMeta[i] = wtMeta[i].replace('#QTY#', $('#hdn_' + rbId + '_qty')[0].value + ';#QTY#');
            if ($('#hdn_' + rbId + '_extSav')[0].value == '1')
                wtMeta[i] = wtMeta[i].replace('#HASEXT#', '1;#HASEXT#');
            else
                wtMeta[i] = wtMeta[i].replace('#HASEXT#', '0;#HASEXT#');
            if ($('#hdn_' + rbId + '_unitSav')[0].value == '1')
                wtMeta[i] = wtMeta[i].replace('#HASUNIT#', '1;#HASUNIT#');
            else
                wtMeta[i] = wtMeta[i].replace('#HASUNIT#', '0;#HASUNIT#');
            wtMeta[i] = wtMeta[i].replace('#SAVINGS#', $('#hdn_' + rbId + '_savings')[0].value + ';#SAVINGS#');
        }
    }
    return wtMeta;
}

function doAnalyticsAddPart(add) {
    var meta;

    if (add)
        meta = ["WT.z_ref_page_type", "SC", "WT.z_ref_page_sub_type", "CO", "WT.z_ref_page_id", "EP", "WT.z_ref_page_event", "Accept Recommendation", "WT.dl", "2", "WT.cg_n", "", "WT.cg_s", ""];
    else
        meta = ["WT.z_ref_page_type", "SC", "WT.z_ref_page_sub_type", "CO", "WT.z_ref_page_id", "EP", "WT.z_ref_page_event", "Reject Recommendation", "WT.dl", "2", "WT.cg_n", "", "WT.cg_s", ""];

    var meta2 = ["WT.pn_sku", "#SKU#", "WT.z_part_id", "#PARTID#", "WT.tx_u", "#QTY#", "WT.z_offer_type", "#OFFERTYPE#", "WT.z_accepted_extended_price_savings", "#ACCEPTEXT#", "WT.z_accepted_unit_price_savings", "#ACCEPTUNIT#", "WT.z_amt_extended_price_savings", "#SAVINGS#", "WT.z_dialog_type", "#DIALOGTYPE#", "WT.z_num_choices", "#NUMCHOICES#"];

    meta2 = doAnalyticsAddPartForRadioButton('rb1', meta2);
    meta2 = doAnalyticsAddPartForRadioButton('rb1a', meta2);
    meta2 = doAnalyticsAddPartForRadioButton('rb1b', meta2);
    meta2 = doAnalyticsAddPartForRadioButton('rb1c', meta2);
    meta2 = doAnalyticsAddPartForRadioButton('rb1d', meta2);
    meta2 = doAnalyticsAddPartForRadioButton('rb2', meta2);
    meta2 = doAnalyticsAddPartForRadioButton('rb3', meta2);

    if ($('#chkStopShowing')[0] != null && $('#chkStopShowing')[0].checked)
        meta2.push("WT.z_disable_recommendations", "1");
    else
        meta2.push("WT.z_disable_recommendations", "0");

    for (var i = 0; i < meta2.length; i++){
        meta2[i] = meta2[i].replace('|#SKU#', '')
                .replace(';#PARTID#', '')
                .replace(';#QTY#', '')
                .replace(';#OFFERTYPE#', '')
                .replace(';#ACCEPTEXT#', '')
                .replace(';#ACCEPTUNIT#', '')
                .replace(';#SAVINGS#', '');
    }

    var numChoices = $('[id^=rb][id != "rbDel"]').length;

    var dialogType = "";
    if ((meta2[7].indexOf('Upsell') > -1) && (meta2[7].indexOf('Unavail') > -1)) {
        dialogType = 'Quantity Unavailable in Selected Packaging (';
    }
    else if ((meta2[7].indexOf('Upsell') > -1)) {
        dialogType = 'Value Calculator (';
    }
    else if ((meta2[7].indexOf('Unavail') > -1)) {
        dialogType = 'Quantity Unavailable in Selected Packaging (';
    }
    dialogType += numChoices + ' Options)';

    meta2[15] = meta2[15].replace('#DIALOGTYPE#', dialogType);
    meta2[17] = meta2[17].replace('#NUMCHOICES#', numChoices);

    var combined = meta.concat(meta2);
    dcsMultiTrack.apply(this, combined);
}

function doAnalyticsAddPartForRadioButton(rbId, wtMeta) {
    if ($('#' + rbId)[0] != null) {
        for (var i = 0; i < wtMeta.length; i++){
            wtMeta[i] = wtMeta[i].replace('#OFFERTYPE#', $('#hdn_' + rbId + '_offerType')[0].value + ';#OFFERTYPE#');
            if ($('#hf_' + rbId +'_selected')[0].value == 'true') {
                wtMeta[i] = wtMeta[i].replace('#SKU#', $('#hdn_' + rbId + '_partWT')[0].value + '|#SKU#');
                wtMeta[i] = wtMeta[i].replace('#PARTID#', $('#hdn_' + rbId + '_partIdWT')[0].value + ';#PARTID#');
                wtMeta[i] = wtMeta[i].replace('#QTY#', $('#hdn_' + rbId + '_qty')[0].value + ';#QTY#');
            }
            else {
                wtMeta[i] = wtMeta[i].replace('#SKU#', '|#SKU#');
                wtMeta[i] = wtMeta[i].replace('#PARTID#', ';#PARTID#');
                wtMeta[i] = wtMeta[i].replace('#QTY#', ';#QTY#');
            }

            if ($('#hf_' + rbId + '_selected')[0].value == 'true' && $('#hdn_' + rbId + '_extSav')[0].value == '1')
                wtMeta[i] = wtMeta[i].replace('#ACCEPTEXT#', '1;#ACCEPTEXT#');
            else
                wtMeta[i] = wtMeta[i].replace('#ACCEPTEXT#', '0;#ACCEPTEXT#');

            if ($('#hf_' + rbId + '_selected')[0].value == 'true' && $('#hdn_' + rbId + '_unitSav')[0].value == '1')
                wtMeta[i] = wtMeta[i].replace('#ACCEPTUNIT#', '1;#ACCEPTUNIT#');
            else
                wtMeta[i] = wtMeta[i].replace('#ACCEPTUNIT#', '0;#ACCEPTUNIT#');

            if ($('#hf_' + rbId + '_selected')[0].value == 'true' && ($('#hdn_' + rbId + '_extSav')[0].value == '1' || $('#hdn_' + rbId + '_unitSav')[0].value == '1'))
                wtMeta[i] = wtMeta[i].replace('#SAVINGS#', $('#hdn_' + rbId + '_savings')[0].value + ';#SAVINGS#');
            else
                wtMeta[i] = wtMeta[i].replace('#SAVINGS#', '0;#SAVINGS#');
        }
    }
    return wtMeta;
}