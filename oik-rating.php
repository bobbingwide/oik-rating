<?php
/**
Plugin Name: oik-rating
Depends: oik base plugin, oik fields
Plugin URI: http://www.oik-plugins.com/oik-plugins/oik-rating
Description: Implements a star rating field using jQuery raty
Version: 0.3
Author: bobbingwide
Author URI: http://www.bobbingwide.com
License: GPL2

    Copyright 2013,2014 Bobbing Wide (email : herb@bobbingwide.com )

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 2,
    as published by the Free Software Foundation.

    You may NOT assume that you can use any other version of the GPL.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    The license for this software can likely be found here:
    http://www.gnu.org/licenses/gpl-2.0.html

*/

/**
 * Implements action "oik_pre_theme_field"
 *
 * The rating field is only required when we intend to actually display the field
 *
 */
function oikr8_pre_theme_field() {
  oik_require( "includes/oik-rating.inc", "oik-rating" );
} 

/**
 * Implements action "oik_pre_form_field"
 *
 * The rating field is only required when we intend to actually to set a new value for the field
 *
 */
function oikr8_pre_form_field() {
  oik_require( "includes/oik-rating.inc", "oik-rating" );
} 

/**
 * Validate a rating field
 *
 * We only check for is_numeric() so that we can support half ratings **?** 2013/07/23
 * 
 * @param string $value - the field value
 * @param string $field - the field name
 * @param array $data - array of data about the field   
 */
function oikr8_field_validation_rating( $value, $field, $data ) {
  // bw_trace2();
  $numeric = is_numeric( $value );
  if ( !$numeric ) {
    $text = sprintf( __( "Invalid %s" ), $data['#title'] );     
    bw_issue_message( $field, "non_numeric", $text, "error" );
  }     
  return( $value );   
}

/**
 * Implement "oik_query_field_types" for oik-rating
 * 
 */
function oikr8_query_field_types( $field_types ) {
  $field_types['rating'] = __( "rating - 5 star rating field", 'oik-rating' ); 
  return( $field_types );
}
 
/**
 * Perform initialisation when plugin file loaded 
 *
 * This plugin doesn't really need to do anything until someone requests a "rating" field to be formatted
 * BUT at present there isn't an action to respond to **?** 2013/07/02
 * 
 */
function oikr8_plugin_loaded() {
  add_action( "oik_pre_theme_field", "oikr8_pre_theme_field" );
  add_action( "oik_pre_form_field", "oikr8_pre_form_field" );
  add_filter( "bw_field_validation_rating", "oikr8_field_validation_rating", 10, 3 );
  add_filter( "oik_query_field_types", "oikr8_query_field_types" );
}

oikr8_plugin_loaded();  
