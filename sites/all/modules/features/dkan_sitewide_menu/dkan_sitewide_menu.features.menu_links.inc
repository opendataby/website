<?php
/**
 * @file
 * dkan_sitewide_menu.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function dkan_sitewide_menu_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_-:groups
  $menu_links['main-menu_-:groups'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'groups',
    'router_path' => 'groups',
    'link_title' => 'Группы данных',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_-:groups',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: main-menu_-:node/1
  $menu_links['main-menu_-:node/1'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'О нас',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'main-menu_-:node/1',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: main-menu_:<front>
  $menu_links['main-menu_:<front>'] = array(
    'menu_name' => 'main-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Справка',
    'options' => array(
      'attributes' => array(
        'title' => 'Справка',
      ),
      'identifier' => 'main-menu_:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: main-menu_:blog
  $menu_links['main-menu_:blog'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'blog',
    'router_path' => 'blog',
    'link_title' => 'Блог',
    'options' => array(
      'attributes' => array(
        'title' => 'Блог',
      ),
      'identifier' => 'main-menu_:blog',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: main-menu_:dataset
  $menu_links['main-menu_:dataset'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'dataset',
    'router_path' => 'dataset',
    'link_title' => 'Данные',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_:dataset',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: main-menu_:node/469
  $menu_links['main-menu_:node/469'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/469',
    'router_path' => 'node/%',
    'link_title' => 'Разработчикам',
    'options' => array(
      'attributes' => array(
        'title' => 'Разработчикам и журналистам',
      ),
      'identifier' => 'main-menu_:node/469',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_:<front>',
  );
  // Exported menu link: main-menu_:node/470
  $menu_links['main-menu_:node/470'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/470',
    'router_path' => 'node/%',
    'link_title' => 'Глоссарий',
    'options' => array(
      'attributes' => array(
        'title' => 'Глоссарий',
      ),
      'identifier' => 'main-menu_:node/470',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_:<front>',
  );
  // Exported menu link: main-menu_:projects
  $menu_links['main-menu_:projects'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'projects',
    'router_path' => 'projects',
    'link_title' => 'Проекты',
    'options' => array(
      'attributes' => array(
        'title' => 'Проекты',
      ),
      'identifier' => 'main-menu_:projects',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: main-menu_add-dataset:node/add/dataset
  $menu_links['main-menu_add-dataset:node/add/dataset'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/dataset',
    'router_path' => 'node/add/dataset',
    'link_title' => 'Add Dataset',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_add-dataset:node/add/dataset',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_stories:stories
  $menu_links['main-menu_stories:stories'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'stories',
    'router_path' => 'stories',
    'link_title' => 'Stories',
    'options' => array(
      'identifier' => 'main-menu_stories:stories',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_-:node/1
  $menu_links['menu-footer-menu_-:node/1'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'node/1',
    'router_path' => 'node/%',
    'link_title' => 'О нас',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_-:node/1',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_:blog
  $menu_links['menu-footer-menu_:blog'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'blog',
    'router_path' => 'blog',
    'link_title' => 'Блог',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_:blog',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_:dataset
  $menu_links['menu-footer-menu_:dataset'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'dataset',
    'router_path' => 'dataset',
    'link_title' => 'Данные',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_:dataset',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_:projects
  $menu_links['menu-footer-menu_:projects'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'projects',
    'router_path' => 'projects',
    'link_title' => 'Проекты',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_:projects',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_facebook-:https://www.facebook.com/groups/opendataby
  $menu_links['menu-footer-menu_facebook-:https://www.facebook.com/groups/opendataby'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'https://www.facebook.com/groups/opendataby',
    'router_path' => '',
    'link_title' => 'Facebook группа',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_facebook-:https://www.facebook.com/groups/opendataby',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-footer-menu_google-:https://groups.google.com/forum/#!forum/opendata-belarus
  $menu_links['menu-footer-menu_google-:https://groups.google.com/forum/#!forum/opendata-belarus'] = array(
    'menu_name' => 'menu-footer-menu',
    'link_path' => 'https://groups.google.com/forum/#!forum/opendata-belarus',
    'router_path' => '',
    'link_title' => 'Google группа',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'menu-footer-menu_google-:https://groups.google.com/forum/#!forum/opendata-belarus',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Add Dataset');
  t('Facebook группа');
  t('Google группа');
  t('Stories');
  t('Блог');
  t('Глоссарий');
  t('Группы данных');
  t('Данные');
  t('О нас');
  t('Проекты');
  t('Разработчикам');
  t('Справка');

  return $menu_links;
}
