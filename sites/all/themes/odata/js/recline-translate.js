(function ($) {
    Drupal.behaviors.reclineTranslate = {
        attach : function(context, settings) {
            window.onload=function(){

                var number = $( ".doc-count").text();
               // var remove = $('.action-remove-series').wrap('<a href="#remove">Удалить</a>');
                $( "button:contains('Grid')" ).text( "Сетка" );
                $( "button:contains('Graph')" ).text( "График" );
                $( "button:contains('Map')" ).text( "Карта" );
                $( "button:contains('Filters')" ).text( "Фильтры" );
                $( "button:contains('Fields')" ).text( "Поля" );
                $( "button:contains('Add Series')" ).text("Добавить Серии");
                $( "label:contains('Graph Type')" ).text( "Тип графика" );
                $( "label:contains('Group Column (Axis 1)')" ).text( "Групповая колонка (Ось 1)" );
                $( "label:contains('Series A (Axis 2)')")
                    .replaceWith( '<label>Серия А (Ось 2) <span></span>[ <a class="action-remove-series" href="#remove"> Удалить </a>]</label> ');
                $( "label:contains('Series B (Axis 2)')")
                    .replaceWith( '<label>Серия B (Ось 2) <span></span>[ <a class="action-remove-series" href="#remove"> Удалить </a>]</label> ');
                $( ".recline-results-info:contains('records')" ).text( "Количество записей: "+number );
            }
        }
    };
})(jQuery);

