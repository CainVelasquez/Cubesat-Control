function QuantityTextBoxOnFocus(element) {
    $('[data-zoomimage]').unbind();
    getPriceBreakPanel(element);
    if($(element).attr('data-popbehavior') !== null && $find($(element).attr('data-popbehavior')) !== null) $find($(element).attr('data-popbehavior')).showPopup();
    window.ResizePopup = $(element).attr('data-popbehavior');
    window.ResizeElement = element;
    $(window).resize(function () {
        windowResizeWithPopupVisible();
        waitForFinalEvent(function () {
            $find(window.ResizePopup).showPopup();
            var $element = $(window.ResizeElement);
            var $panel = $("[id$='" + $element.attr('data-panel') + "']");
            var elementLeft = $element.position().left;
            if ($panel.width() > 0) {
                if ($("html").attr("dir") === "rtl") {
                    $panel.css("left", elementLeft + $element.width() - $panel.width() - 25);
                } else {
                    $panel.css("left", elementLeft);
                }
            }
        }, 500, "qtyTextBoxOnFocus");
    });
    var $element = $(element);
    var $panel = $("[id$='" + $element.attr('data-panel') + "']");
    var elementLeft = $element.position().left;
    if ($panel.width() > 0) {
        if ($("html").attr("dir") === "rtl") {
            $panel.css("left", elementLeft + $element.width() - $panel.width() - 25);
        } else {
            $panel.css("left", elementLeft);
        }
    }
}

function QuantityTextBoxOnBlur(element) {
    var $element = $(element);
    $('[data-zoomimage]').hover(ImageHover, ImageBlur);
    $find($element.attr('data-popbehavior')).hidePopup();
    $(window).unbind();
    window.ResizePopup = "";
    window.ResizeElement = "";
    if ($element.val() === "") {
        $element.val($element.attr("data-prevvalue"));
        Page_ClientValidate("inlinequantity");

    } else if (!Page_ClientValidate("inlinequantity")) {
        var args = { Value: $element.val(), IsValid: true };
        validateQuantity(null, args);
        if (args.IsValid) {
            changeQty($element.id, '', 'valid');
        }
    }
}

var waitForFinalEvent = (function () {
    var timers = {};
    return function (callback, ms, uniqueId) {
        if (!uniqueId) {
            uniqueId = "Don't call this twice without a uniqueId";
        }
        if (timers[uniqueId]) {
            clearTimeout(timers[uniqueId]);
        }
        timers[uniqueId] = setTimeout(callback, ms);
    };
})();

function windowResizeWithPopupVisible() {
    if (window.ResizePopup && window.ResizePopup !== "") {
        $find(window.ResizePopup).hidePopup();
    }
}

function validateQuantity(sender, args) {
    var integer = parseInt(args.Value);
    if (args.Value === "" || isNaN(args.Value) || integer < 1) args.IsValid = false;
}

function changeQty(eventTarget, eventArgument, validationGroup) {
    if (typeof (Page_ClientValidate) === 'function') {
        Page_ClientValidate(validationGroup);
        if (Page_IsValid) {
            if (typeof (fireWebTrendsQuantityChangedTag) === 'function') fireWebTrendsQuantityChangedTag();
            __doPostBack(eventTarget, eventArgument);
            return Page_IsValid;
        }
    }
    else {
        if (typeof (fireWebTrendsQuantityChangedTag) === 'function') fireWebTrendsQuantityChangedTag();
        __doPostBack(eventTarget, eventArgument);
        return true;
    }
}

function getPriceBreakPanel(element) {
    var $element = $(element);
    var partNumber = $element.attr('data-reportpartnumber');
    var panel = $element.attr('data-panel');
    var pnl = $("[id$='" + panel + "']");
    if (pnl.attr('done') === 'true' || pnl.attr('done') === 'inprogress') {
        return;
    }
    pnl.attr('done', 'inprogress');
    var url = '/classic/ordering/dialog/pricebreaktable.aspx?reportpartnumber=' + encodeURIComponent(partNumber);
    if (window.location.host.startsWith("local")) url = url.replace("classic", "localordering");
    $.ajax({
        url: url,
        success: function (data) {
            if ($(data).find("[id$='pnlPriceBreaks']").length === 0) {
                $("[id$='" + panel + "']").removeClass("psshadow");
            } else {
                $("[id$='" + panel + "']").append(data);

                $("[id$='" + panel + "']").attr('done', 'true');
                var $panel = $("[id$='" + $element.attr('data-panel') + "']");
                var goodResponse = $(data).find("pnlPriceBreaks");
                if (goodResponse) {
                    $panel.attr("class", "psshadow");
                }
                var elementLeft = $element.position().left;
                if ($("html").attr("dir") === "rtl") {
                    $panel.css("left", elementLeft + $element.width() - $panel.width() - 25);
                } else {
                    $panel.css("left", elementLeft);
                }
            }
        },
        error: function () {
            $("[id$='" + panel + "']").attr("class", "");
            $("[id$='" + panel + "']").removeClass("psshadow");
        }
    });
}

$(document).ready(function () {
    window.schedulesDialogActive = false;
    $(".sodisplay input").keypress(function (event) {
        if (event.which == 13) {
            $(this).blur();
        }
    });
});