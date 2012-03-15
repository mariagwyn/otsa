/*
 * @file
 * Javascript for showing and hiding dependent attributes.
 *
 * Retrieves the dependencies from the database using a callback and shows
 * and hides attributes depending upon the value selected for the attribute
 * they depend upon.
 */

(function ($) {

  Drupal.behaviors.uc_dropdown_attributes = {
    attach: function (context, settings) {
      // Retrieve the node id
      if ($('div.product-kit').html()) {
        $('div.add-to-cart').find(':input[name$="[nid]"]').each( function(i,val) {
          var nid = $(val).val();
          $('fieldset#edit-products-' + nid).find('div.attribute').each( function(i,val) {
            var attributes = $(val).attr('class').split(' ');
            if (attributes[1] != undefined) {
              var aid = attributes[1].split('-')[1];
              $.get(Drupal.settings.basePath + 'node/' + nid +
                    '/dependencies/' + aid + '/children', null,
                    parentAttribute);
            }
          });
        });
      }
      else {
        $('div.add-to-cart').each(function(i,val) {
          nid = $(val).find(':input[name="node_id"]').val();
          $(val).find('div.attribute').each( function(i,val) {
            var attributes = $(val).attr('class').split(' ');
            if (attributes[1] != undefined) {
              var aid = attributes[1].split('-')[1];
              $.get(Drupal.settings.basePath + 'node/' + nid +
                    '/dependencies/' + aid + '/children', null,
                    parentAttribute);
            }
          });
        });
      }
    }
  };

  var parentAttribute = function(response) {
    if (response.status) {
      type = getType('.attribute-' + response.parent_aid);
      switch(type) {
      case 'select':
        $('.attribute-' + response.parent_aid).find('select').change(function() {
          $.each(response.aid, function(index, aid) {
            $.get(Drupal.settings.basePath + 'node/' + response.nid +
                  '/dependencies/' + aid + '/dependency', null, applyAttribute);
          });
        });
        break;
      case 'radio':
        $('.attribute-' + response.parent_aid).find('input[name="attributes[' + response.parent_aid + ']"]').change(function() {
          $.each(response.aid, function(index, aid) {
            $.get(Drupal.settings.basePath + 'node/' + response.nid +
                  '/dependencies/' + aid + '/dependency', null, applyAttribute);
          });
        });
        break;
      case 'checkbox':
        $('.attribute-' + response.parent_aid).find('input:checkbox').change(function() {
        $.each(response.aid, function(index, aid) {
          $.get(Drupal.settings.basePath + 'node/' + response.nid +
                '/dependencies/' + aid + '/dependency', null, applyAttribute);
        });
      });
        break;
      default:
        break;
      }
    }
  };

  var applyAttribute = function(response) {
    if (response.status) {
      parentType = getType('.attribute-' + response.parent_aid);
      var values;
      switch(parentType) {
      case 'select':
        values = [];
        value = $('.attribute-' + response.parent_aid).find('select').val();
        if (value !== '') {
            values.push(value);
        }
        break;
      case 'radio':
        value = $('.attribute-' + response.parent_aid).find('input[name="attributes[' + response.parent_aid + ']"]:checked').val();
        values = [value];
        break;
      case 'checkbox':
        values = [];
        $.each($('.attribute-' + response.parent_aid).find('input:checkbox:checked'), function() {
          values.push($(this).val());
        });
        break;
      default:
        break;
      }
      type = getType('.attribute-' + response.aid);
      switch(type) {
      case 'select':
      case 'radio':
      case 'checkbox':
      case 'text':
        if (!intersection(values, response.parent_values)) {
          $('.attribute-' + response.aid).html('');
          $.get(Drupal.settings.basePath + 'node/' + response.nid +
                '/dependencies/' + response.aid + '/children', null,
                removeChildren);
        }
        break;
      default:
        if (intersection(values, response.parent_values)) {
          $('.attribute-' + response.aid).html(response.html);
          $.get(Drupal.settings.basePath + 'node/' + response.nid +
                '/dependencies/' + response.aid + '/children', null,
                parentAttribute);
          if (response.required == 1) {
            label = $('.attribute-' + response.aid).find('label').not('.option');
            $(label).replaceWith('<label>' +$(label).text() + '<span class="form-required" title="' + Drupal.t('This field is required.') + '">*</span></label>');
          }
        }
        break;
      }
    }
  };

  var getType = function(attribute) {
    type = $(attribute).find('input').attr('type');
    if (type=='radio' || type=='text' || type=='checkbox') {
      return type;
    }
    type = $(attribute).find('select').attr('class');
    if (type == undefined) {
      return type;
    }
    else {
      return 'select';
    }
  };

  var removeChildren = function(response) {
    if (response.status) {
      $.each(response.aid, function(index, aid) {
        $.get(Drupal.settings.basePath + 'node/' + response.nid +
              '/dependencies/' + aid + '/children', null,
              removeChildren);
        $('.attribute-' + aid).html('');
      });
    }
  };

  var intersection = function(array, object) {
    for (var i=0; i<array.length; i++) {
      if (object[array[i]] != undefined) {
        return true;
      }
    }
    return false;
  };

})(jQuery);
