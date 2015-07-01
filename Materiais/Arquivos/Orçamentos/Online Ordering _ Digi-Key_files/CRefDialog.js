
function disableNewCref() {
    document.getElementById('txtNewRef').setAttribute('disabled', 'disabled');
    document.getElementById('txtNewRef').setAttribute('class', 'aspNetDisabled');
    document.getElementById('lblReq').style.display = 'none';
}

function enableNewCref() {
    document.getElementById('txtNewRef').removeAttribute('disabled');
    document.getElementById('txtNewRef').removeAttribute('class');
    document.getElementById('txtNewRef').focus();
}

function addPartFromCRefDialog() {
    if ($('input[name=rbgCRefs]:checked').val() == 'newCustomerReference' && document.getElementById('txtNewRef').value.trim() == '') {
        document.getElementById('lblReq').style.display = 'inline';
        return false;
    }
    else {
        return true;
    }
}
