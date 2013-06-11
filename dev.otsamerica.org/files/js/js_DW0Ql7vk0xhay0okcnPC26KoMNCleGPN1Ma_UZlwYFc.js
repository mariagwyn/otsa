(function ($) {

Drupal.behaviors.textarea = {
  attach: function (context, settings) {
    $('.form-textarea-wrapper.resizable', context).once('textarea', function () {
      var staticOffset = null;
      var textarea = $(this).addClass('resizable-textarea').find('textarea');
      var grippie = $('<div class="grippie"></div>').mousedown(startDrag);

      grippie.insertAfter(textarea);

      function startDrag(e) {
        staticOffset = textarea.height() - e.pageY;
        textarea.css('opacity', 0.25);
        $(document).mousemove(performDrag).mouseup(endDrag);
        return false;
      }

      function performDrag(e) {
        textarea.height(Math.max(32, staticOffset + e.pageY) + 'px');
        return false;
      }

      function endDrag(e) {
        $(document).unbind('mousemove', performDrag).unbind('mouseup', endDrag);
        textarea.css('opacity', 1);
      }
    });
  }
};

})(jQuery);
;
(function ($) {

/**
 * Toggle the visibility of a fieldset using smooth animations.
 */
Drupal.toggleFieldset = function (fieldset) {
  var $fieldset = $(fieldset);
  if ($fieldset.is('.collapsed')) {
    var $content = $('> .fieldset-wrapper', fieldset).hide();
    $fieldset
      .removeClass('collapsed')
      .trigger({ type: 'collapsed', value: false })
      .find('> legend span.fieldset-legend-prefix').html(Drupal.t('Hide'));
    $content.slideDown({
      duration: 'fast',
      easing: 'linear',
      complete: function () {
        Drupal.collapseScrollIntoView(fieldset);
        fieldset.animating = false;
      },
      step: function () {
        // Scroll the fieldset into view.
        Drupal.collapseScrollIntoView(fieldset);
      }
    });
  }
  else {
    $fieldset.trigger({ type: 'collapsed', value: true });
    $('> .fieldset-wrapper', fieldset).slideUp('fast', function () {
      $fieldset
        .addClass('collapsed')
        .find('> legend span.fieldset-legend-prefix').html(Drupal.t('Show'));
      fieldset.animating = false;
    });
  }
};

/**
 * Scroll a given fieldset into view as much as possible.
 */
Drupal.collapseScrollIntoView = function (node) {
  var h = document.documentElement.clientHeight || document.body.clientHeight || 0;
  var offset = document.documentElement.scrollTop || document.body.scrollTop || 0;
  var posY = $(node).offset().top;
  var fudge = 55;
  if (posY + node.offsetHeight + fudge > h + offset) {
    if (node.offsetHeight > h) {
      window.scrollTo(0, posY);
    }
    else {
      window.scrollTo(0, posY + node.offsetHeight - h + fudge);
    }
  }
};

Drupal.behaviors.collapse = {
  attach: function (context, settings) {
    $('fieldset.collapsible', context).once('collapse', function () {
      var $fieldset = $(this);
      // Expand fieldset if there are errors inside, or if it contains an
      // element that is targeted by the uri fragment identifier. 
      var anchor = location.hash && location.hash != '#' ? ', ' + location.hash : '';
      if ($('.error' + anchor, $fieldset).length) {
        $fieldset.removeClass('collapsed');
      }

      var summary = $('<span class="summary"></span>');
      $fieldset.
        bind('summaryUpdated', function () {
          var text = $.trim($fieldset.drupalGetSummary());
          summary.html(text ? ' (' + text + ')' : '');
        })
        .trigger('summaryUpdated');

      // Turn the legend into a clickable link, but retain span.fieldset-legend
      // for CSS positioning.
      var $legend = $('> legend .fieldset-legend', this);

      $('<span class="fieldset-legend-prefix element-invisible"></span>')
        .append($fieldset.hasClass('collapsed') ? Drupal.t('Show') : Drupal.t('Hide'))
        .prependTo($legend)
        .after(' ');

      // .wrapInner() does not retain bound events.
      var $link = $('<a class="fieldset-title" href="#"></a>')
        .prepend($legend.contents())
        .appendTo($legend)
        .click(function () {
          var fieldset = $fieldset.get(0);
          // Don't animate multiple times.
          if (!fieldset.animating) {
            fieldset.animating = true;
            Drupal.toggleFieldset(fieldset);
          }
          return false;
        });

      $legend.append(summary);
    });
  }
};

})(jQuery);
;
(function ($) {

/**
 * Attaches the autocomplete behavior to all required fields.
 */
Drupal.behaviors.autocomplete = {
  attach: function (context, settings) {
    var acdb = [];
    $('input.autocomplete', context).once('autocomplete', function () {
      var uri = this.value;
      if (!acdb[uri]) {
        acdb[uri] = new Drupal.ACDB(uri);
      }
      var $input = $('#' + this.id.substr(0, this.id.length - 13))
        .attr('autocomplete', 'OFF')
        .attr('aria-autocomplete', 'list');
      $($input[0].form).submit(Drupal.autocompleteSubmit);
      $input.parent()
        .attr('role', 'application')
        .append($('<span class="element-invisible" aria-live="assertive"></span>')
          .attr('id', $input.attr('id') + '-autocomplete-aria-live')
        );
      new Drupal.jsAC($input, acdb[uri]);
    });
  }
};

/**
 * Prevents the form from submitting if the suggestions popup is open
 * and closes the suggestions popup when doing so.
 */
Drupal.autocompleteSubmit = function () {
  return $('#autocomplete').each(function () {
    this.owner.hidePopup();
  }).size() == 0;
};

/**
 * An AutoComplete object.
 */
Drupal.jsAC = function ($input, db) {
  var ac = this;
  this.input = $input[0];
  this.ariaLive = $('#' + $input.attr('id') + '-autocomplete-aria-live');
  this.db = db;

  $input
    .keydown(function (event) { return ac.onkeydown(this, event); })
    .keyup(function (event) { ac.onkeyup(this, event); })
    .blur(function () { ac.hidePopup(); ac.db.cancel(); });

};

/**
 * Handler for the "keydown" event.
 */
Drupal.jsAC.prototype.onkeydown = function (input, e) {
  if (!e) {
    e = window.event;
  }
  switch (e.keyCode) {
    case 40: // down arrow.
      this.selectDown();
      return false;
    case 38: // up arrow.
      this.selectUp();
      return false;
    default: // All other keys.
      return true;
  }
};

/**
 * Handler for the "keyup" event.
 */
Drupal.jsAC.prototype.onkeyup = function (input, e) {
  if (!e) {
    e = window.event;
  }
  switch (e.keyCode) {
    case 16: // Shift.
    case 17: // Ctrl.
    case 18: // Alt.
    case 20: // Caps lock.
    case 33: // Page up.
    case 34: // Page down.
    case 35: // End.
    case 36: // Home.
    case 37: // Left arrow.
    case 38: // Up arrow.
    case 39: // Right arrow.
    case 40: // Down arrow.
      return true;

    case 9:  // Tab.
    case 13: // Enter.
    case 27: // Esc.
      this.hidePopup(e.keyCode);
      return true;

    default: // All other keys.
      if (input.value.length > 0)
        this.populatePopup();
      else
        this.hidePopup(e.keyCode);
      return true;
  }
};

/**
 * Puts the currently highlighted suggestion into the autocomplete field.
 */
Drupal.jsAC.prototype.select = function (node) {
  this.input.value = $(node).data('autocompleteValue');
};

/**
 * Highlights the next suggestion.
 */
Drupal.jsAC.prototype.selectDown = function () {
  if (this.selected && this.selected.nextSibling) {
    this.highlight(this.selected.nextSibling);
  }
  else if (this.popup) {
    var lis = $('li', this.popup);
    if (lis.size() > 0) {
      this.highlight(lis.get(0));
    }
  }
};

/**
 * Highlights the previous suggestion.
 */
Drupal.jsAC.prototype.selectUp = function () {
  if (this.selected && this.selected.previousSibling) {
    this.highlight(this.selected.previousSibling);
  }
};

/**
 * Highlights a suggestion.
 */
Drupal.jsAC.prototype.highlight = function (node) {
  if (this.selected) {
    $(this.selected).removeClass('selected');
  }
  $(node).addClass('selected');
  this.selected = node;
  $(this.ariaLive).html($(this.selected).html());
};

/**
 * Unhighlights a suggestion.
 */
Drupal.jsAC.prototype.unhighlight = function (node) {
  $(node).removeClass('selected');
  this.selected = false;
  $(this.ariaLive).empty();
};

/**
 * Hides the autocomplete suggestions.
 */
Drupal.jsAC.prototype.hidePopup = function (keycode) {
  // Select item if the right key or mousebutton was pressed.
  if (this.selected && ((keycode && keycode != 46 && keycode != 8 && keycode != 27) || !keycode)) {
    this.input.value = $(this.selected).data('autocompleteValue');
  }
  // Hide popup.
  var popup = this.popup;
  if (popup) {
    this.popup = null;
    $(popup).fadeOut('fast', function () { $(popup).remove(); });
  }
  this.selected = false;
  $(this.ariaLive).empty();
};

/**
 * Positions the suggestions popup and starts a search.
 */
Drupal.jsAC.prototype.populatePopup = function () {
  var $input = $(this.input);
  var position = $input.position();
  // Show popup.
  if (this.popup) {
    $(this.popup).remove();
  }
  this.selected = false;
  this.popup = $('<div id="autocomplete"></div>')[0];
  this.popup.owner = this;
  $(this.popup).css({
    top: parseInt(position.top + this.input.offsetHeight, 10) + 'px',
    left: parseInt(position.left, 10) + 'px',
    width: $input.innerWidth() + 'px',
    display: 'none'
  });
  $input.before(this.popup);

  // Do search.
  this.db.owner = this;
  this.db.search(this.input.value);
};

/**
 * Fills the suggestion popup with any matches received.
 */
Drupal.jsAC.prototype.found = function (matches) {
  // If no value in the textfield, do not show the popup.
  if (!this.input.value.length) {
    return false;
  }

  // Prepare matches.
  var ul = $('<ul></ul>');
  var ac = this;
  for (key in matches) {
    $('<li></li>')
      .html($('<div></div>').html(matches[key]))
      .mousedown(function () { ac.select(this); })
      .mouseover(function () { ac.highlight(this); })
      .mouseout(function () { ac.unhighlight(this); })
      .data('autocompleteValue', key)
      .appendTo(ul);
  }

  // Show popup with matches, if any.
  if (this.popup) {
    if (ul.children().size()) {
      $(this.popup).empty().append(ul).show();
      $(this.ariaLive).html(Drupal.t('Autocomplete popup'));
    }
    else {
      $(this.popup).css({ visibility: 'hidden' });
      this.hidePopup();
    }
  }
};

Drupal.jsAC.prototype.setStatus = function (status) {
  switch (status) {
    case 'begin':
      $(this.input).addClass('throbbing');
      $(this.ariaLive).html(Drupal.t('Searching for matches...'));
      break;
    case 'cancel':
    case 'error':
    case 'found':
      $(this.input).removeClass('throbbing');
      break;
  }
};

/**
 * An AutoComplete DataBase object.
 */
Drupal.ACDB = function (uri) {
  this.uri = uri;
  this.delay = 300;
  this.cache = {};
};

/**
 * Performs a cached and delayed search.
 */
Drupal.ACDB.prototype.search = function (searchString) {
  var db = this;
  this.searchString = searchString;

  // See if this string needs to be searched for anyway.
  searchString = searchString.replace(/^\s+|\s+$/, '');
  if (searchString.length <= 0 ||
    searchString.charAt(searchString.length - 1) == ',') {
    return;
  }

  // See if this key has been searched for before.
  if (this.cache[searchString]) {
    return this.owner.found(this.cache[searchString]);
  }

  // Initiate delayed search.
  if (this.timer) {
    clearTimeout(this.timer);
  }
  this.timer = setTimeout(function () {
    db.owner.setStatus('begin');

    // Ajax GET request for autocompletion.
    $.ajax({
      type: 'GET',
      url: db.uri + '/' + encodeURIComponent(searchString),
      dataType: 'json',
      success: function (matches) {
        if (typeof matches.status == 'undefined' || matches.status != 0) {
          db.cache[searchString] = matches;
          // Verify if these are still the matches the user wants to see.
          if (db.searchString == searchString) {
            db.owner.found(matches);
          }
          db.owner.setStatus('found');
        }
      },
      error: function (xmlhttp) {
        alert(Drupal.ajaxError(xmlhttp, db.uri));
      }
    });
  }, this.delay);
};

/**
 * Cancels the current autocomplete request.
 */
Drupal.ACDB.prototype.cancel = function () {
  if (this.owner) this.owner.setStatus('cancel');
  if (this.timer) clearTimeout(this.timer);
  this.searchString = '';
};

})(jQuery);
;

/**
 * @file shows / hides form elements
 */
 
(function ($) {

Drupal.behaviors.TaxonomyManagerHideForm = {
  attach: function(context, settings) {
    if (!$('#taxonomy-manager-toolbar').hasClass('buttons-processed')) {
      $('#taxonomy-manager-toolbar').addClass('buttons-processed')
      settings = settings.hideForm || [];
      if (settings instanceof Array) {
        for (var i=0; i<settings.length; i++) {
          Drupal.attachHideForm(settings[i].div, settings[i].show_button, settings[i].hide_button);
        }
      }
    }
  }
}

/**
 * adds click events to show / hide button
 */
Drupal.attachHideForm = function(div, show_button, hide_button) {
  var hide = true;
  div = $("#"+ div);
  show_button = $("#"+ show_button);
  hide_button = $("#"+ hide_button);

  // don't hide if there is an error in the form
  $(div).find("input").each(function() {
    if($(this).hasClass("error")) {
      hide = false;
    }
  });
  
  if (!hide) { 
    $(div).show();
  }
  $(show_button).click(function() {
    $(div).toggle();
    return false;
  });
  
  $(hide_button).click(function() {
    $(div).hide();
    return false;
  });
}

})(jQuery);
;

/**
 * @file js for changing weights of terms with Up and Down arrows
 */

(function ($) {

//object to store weights (tid => weight)
var weights = new Object();

Drupal.behaviors.TaxonomyManagerWeights = {
  attach: function(context, settings) {
    var weightSettings = settings.updateWeight || [];
    if (!$('#taxonomy-manager-toolbar.tm-weights-processed').length) {
      $('#taxonomy-manager-toolbar').addClass('tm-weights-processed');
      Drupal.attachUpdateWeightToolbar(weightSettings['up'], weightSettings['down']);
      Drupal.attachUpdateWeightTerms();   
    }  
  }
}

/**
 * adds click events for Up and Down buttons in the toolbar, which
 * allow the moving of selected (can be more) terms
 */
Drupal.attachUpdateWeightToolbar = function(upButton, downButton) {
  var selected;
  var url = Drupal.settings.updateWeight['url'];  
  
  $('#'+ upButton).click(function() {
    selected = Drupal.getSelectedTerms();
    for (var i=0; i < selected.length; i++) {
      var upTerm = selected[i];
      var downTerm = $(upTerm).prev(); 
    
      Drupal.orderTerms(upTerm, downTerm);
    }
    if (selected.length > 0) {
      $.post(url, weights);
    }
  });
  
  
  $('#'+ downButton).click(function() {
    selected = Drupal.getSelectedTerms();
    for (var i=selected.length-1; i >= 0; i--) {
      var downTerm = selected[i];
      var upTerm = $(downTerm).next();
      
      Drupal.orderTerms(upTerm, downTerm);
    }
    if (selected.length > 0) {
      $.post(url, weights);
    }
  });
}

/**
 * adds small up and down arrows to each term
 * arrows get displayed on mouseover
 */
Drupal.attachUpdateWeightTerms = function(parent, currentIndex) {
  var settings = Drupal.settings.updateWeight || [];
  var disable = settings['disable_mouseover'];
 	 
  if (!disable) {
    var url = Drupal.settings.updateWeight['url'];
  
    var termLineClass = 'div.term-line';
    var termUpClass = 'img.term-up';
    var termDownClass = 'img.term-down';
  
    if (parent && currentIndex) {
      parent = $(parent).slice(currentIndex);
    }
    if (parent) {
      termLineClass = $(parent).find(termLineClass);
      termUpClass = $(parent).find(termUpClass);
      termDownClass = $(parent).find(termDownClass);
    }
  
    $(termLineClass).mouseover(function() {
      $(this).find('div.term-operations').show(); 
    });
  
    $(termLineClass).mouseout(function() {
      $(this).find('div.term-operations').hide(); 
    });
  
    $(termUpClass).click(function() {
      var upTerm = $(this).parents("li").eq(0);
      var downTerm = $(upTerm).prev(); 
    
      Drupal.orderTerms(upTerm, downTerm);
      $.post(url, weights);
    
      $(downTerm).find(termLineClass).unbind('mouseover');
      setTimeout(function() {
        $(upTerm).find('div.term-operations').hide();
        $(downTerm).find(termLineClass).mouseover(function() {
          $(this).find('div.term-operations').show();
        });
      }, 1500);
    
    });
  
  
    $(termDownClass).click(function() {
      var downTerm = $(this).parents("li").eq(0);
      var upTerm = $(downTerm).next();
    
      Drupal.orderTerms(upTerm, downTerm);
      $.post(url, weights);
    
      $(upTerm).find(termLineClass).unbind('mouseover');
      setTimeout(function() {
        $(downTerm).find('div.term-operations').hide();
        $(upTerm).find(termLineClass).mouseover(function() {
          $(this).find('div.term-operations').show();
        });
      }, 1500);
    
    });
  }

}

/**
 * return array of selected terms
 */
Drupal.getSelectedTerms = function() {
  var terms = new Array();
  $('.treeview').find("input:checked").each(function() {
    var term = $(this).parents("li").eq(0);
    terms.push(term);
  });
  
  return terms;
}

/**
 * reorders terms
 *   - swap list elements in DOM
 *   - post updated weights to callback in php
 *   - update classes of tree view
 */
Drupal.orderTerms = function(upTerm, downTerm) {
  try {
    Drupal.getTermId(upTerm);
    Drupal.swapTerms(upTerm, downTerm);
    Drupal.swapWeights(upTerm, downTerm);
    Drupal.updateTree(upTerm, downTerm);
  } catch(e) {
    //no next item, because term to update is last child, continue
  }
}

/**
 * simple swap of two elements
 */
Drupal.swapTerms = function(upTerm, downTerm) { 
  $(upTerm).after(downTerm);
  $(downTerm).before(upTerm);
}

/**
 * updating weights of swaped terms
 * if two terms have different weights, then weights are being swapped
 * else, if both have same weights, upTerm gets decreased
 *
 * if prev/next siblings of up/down terms have same weights as current
 * swapped, they have to be updated by de/increasing weight (by 1) to ensure
 * unique position of swapped terms
 */
Drupal.swapWeights = function(upTerm, downTerm) {
  var upWeight = Drupal.getWeight(upTerm);
  var downWeight = Drupal.getWeight(downTerm);
  var downTid = Drupal.getTermId(downTerm);
  var upTid = Drupal.getTermId(upTerm);
  
  //same weight, decrease upTerm
  if (upWeight == downWeight) {
    weights[upTid] = --upWeight;
  }
  //different weights, swap
  else {
    weights[upTid] = downWeight;
    weights[downTid] = upWeight;
  }
  
  //update prev siblings if necessary
  try {
    if (Drupal.getWeight($(upTerm).prev()) >= upWeight) {
      $(upTerm).prevAll().each(function() {
        var id = Drupal.getTermId(this);
        var weight = Drupal.getWeight(this);
        weights[id] = --weight;
      });
    }
  } catch(e) {
    //no prev
  }
  
  //update next siblings if necessary
  try {
    if (Drupal.getWeight($(downTerm).next()) <= downWeight) {
      $(downTerm).nextAll().each(function() {
        var id = Drupal.getTermId(this);
        var weight = Drupal.getWeight(this);
        weights[id] = ++weight;
      });
    }
  } catch(e) {
    //no next
  }

}

/**
 * helper to return weight of a term
 */
Drupal.getWeight = function(li) {
  var id = Drupal.getTermId(li);
  var weight;
  
  if (weights[id] != null) {
    weight = weights[id];
  }
  else {
    weight = $(li).find("input:hidden[class=weight-form]").attr("value");
  }
  
  return weight;
}

})(jQuery);
;

/**
 * @file js support for term editing form for ajax saving and tree updating
 */


(function ($) {
  
//global var that holds the current term link object
var active_term = new Object();

/** 
 * attaches term data form, used after 'Saves changes' submit
 */
Drupal.behaviors.TaxonomyManagerTermData = {
  attach: function(context) {
    if (!$('#taxonomy-term-data-replace').hasClass('processed')) {
      $('#taxonomy-term-data-replace').addClass('processed');
      Drupal.attachTermDataForm();
    }
  }
}

/**
 * attaches Term Data functionality, called by tree.js
 */
Drupal.attachTermData = function(ul) {
  Drupal.attachTermDataLinks(ul);
}

/**
 * adds click events to the term links in the tree structure
 */
Drupal.attachTermDataLinks = function(ul) {
  $(ul).find('a.term-data-link').click(function() {
    Drupal.activeTermSwapHighlight(this);
    var li = $(this).parents("li:first");
    Drupal.loadTermDataForm(Drupal.getTermId(li), false);
    return false;
  });
}

/**
 * attaches click events to next siblings
 */
Drupal.attachTermDataToSiblings = function(all, currentIndex) {
  var nextSiblings = $(all).slice(currentIndex);
  $(nextSiblings).find('a.term-data-link').click(function() {
    var li = $(this).parents("li:first");
    Drupal.loadTermDataForm(Drupal.getTermId(li), false);
    return false;
  });
}

/**
 * adds click events to term data form, which is already open, when page gets loaded
 */
Drupal.attachTermDataForm = function() {
  active_term = $('div.highlightActiveTerm').find('a');
  var tid = $('#taxonomy-term-data').find('input:hidden[name="tid"]').val();
  if (tid) {
    new Drupal.TermData(tid).form();
  }
}

/**
 * loads term data form
 */
Drupal.loadTermDataForm = function(tid, refreshTree) {
  // Triggers an AJAX button
  $('#edit-load-tid').val(tid);
  if (refreshTree) {
    $('#edit-load-tid-refresh-tree').attr("checked", "checked");
  }
  else {
    $('#edit-load-tid-refresh-tree').attr("checked", "");
  }
  $('#edit-load-tid-submit').click();
}

/**
 * TermData Object
 */
Drupal.TermData = function(tid) {
  this.tid = tid;
  this.div = $('#taxonomy-term-data');
}

/**
 * adds events to possible operations
 */
Drupal.TermData.prototype.form = function() {
  var termdata = this;
  
  $(this.div).find('#term-data-close span').click(function() {
    termdata.div.children().hide();
  });
  
  $(this.div).find('a.taxonomy-term-data-name-link').click(function() {
    var tid = this.href.split("/").pop();
    Drupal.loadTermDataForm(tid, true);
    return false;
  });
  
  $(this.div).find("legend").each(function() {
    var staticOffsetX, staticOffsetY = null;
    var left, top = 0;
    var div = termdata.div; 
    var pos = $(div).position();
    $(this).mousedown(startDrag);  
  
    function startDrag(e) {
      if (staticOffsetX == null && staticOffsetY == null) {
        staticOffsetX = e.pageX;
        staticOffsetY = e.pageY;
      }
      $(document).mousemove(performDrag).mouseup(endDrag);
      return false;
    }
 
    function performDrag(e) {
      left = e.pageX - staticOffsetX;
      top = e.pageY - staticOffsetY;
      $(div).css({position: "absolute", "left": pos.left + left +"px", "top": pos.top + top +"px"});
      return false;
    }
 
    function endDrag(e) {
      $(document).unbind("mousemove", performDrag).unbind("mouseup", endDrag);
    }
  });
}

/**
* hightlights current term
*/
Drupal.activeTermSwapHighlight = function(link) {
  try {
    $(active_term).parents('div.term-line').removeClass('highlightActiveTerm');
  } catch(e) {}
  active_term = link;
  $(active_term).parents('div.term-line:first').addClass('highlightActiveTerm');
}

})(jQuery);
;
/** 
 * CSV Export
 *
 * adds click event to export button and makes AJAX call to get the CSV data
 */
(function ($) {

Drupal.behaviors.TaxonomyManagerCSVExport = {
  attach: function(context, settings) {    
    if (!$('#edit-export-show.csv-processed').length) {
      $('#edit-export-show').addClass('csv-processed');
      var url = settings.exportCSV['url'];
      var vid = settings.taxonomytree[0].vid;
  
      $("#edit-export-submit").click(function() {
        var area = $("#edit-export-csv");
        var param = new Object();
        param['delimiter'] = $("#edit-export-delimiter").val();
        param['depth'] = $("#edit-export-depth").val();
        param['option'] = $("#taxonomy_manager_export_options").find("input:checked").val();
        param['vid'] = vid;
        var tid = 0;
        $('.treeview').find("input:checked").each(function() {
         tid = Drupal.getTermId($(this).parents("li").eq(0));
        });
        param['tid'] = tid;
    
        $.post(url, param, function(data) {
          $(area).val(data['csv']);
        });
        return false;
      });
    }
  }
}

})(jQuery);
;
