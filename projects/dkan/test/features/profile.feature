# features/profile.feature
Feature: Profile
  Check a user profile as an authenticated user.

  @api @javascript
  Scenario: Check profile menu
    Given I am logged in as a user with the "authenticated user" role
    And I am on "/user"
    Then I should see "Datasets" in the ".block-dkan-profile-page-user-summary" element
    Then I should see "Groups" in the ".block-dkan-profile-page-user-summary" element
    Then I should see "Profile Settings" in the ".block-dkan-profile-page-user-summary" element
